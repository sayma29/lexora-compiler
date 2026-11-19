
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);

extern int yylineno;

ASTNode *ast_root = NULL;
%}

%code requires {
#include "ast.h"
}

%error-verbose

%union {
    char *str;
    ASTNode *node;
    DataType dtype;
}

%token TOK_INT 258
%token TOK_FLOAT TOK_BOOL
%token TOK_IF TOK_ELSE TOK_WHILE TOK_PRINT
%token TOK_TRUE TOK_FALSE

%token <str> TOK_ID TOK_INTLIT TOK_FLOATLIT

%token TOK_PLUS TOK_MINUS TOK_STAR TOK_SLASH TOK_PERCENT
%token TOK_LT TOK_GT TOK_LE TOK_GE TOK_EQ TOK_NE
%token TOK_AND TOK_OR TOK_NOT TOK_ASSIGN

%token TOK_LBRACE TOK_RBRACE TOK_LPAREN TOK_RPAREN TOK_SEMI

%type <node> program statement_list statement
%type <node> declaration assignment print_statement
%type <node> if_statement while_statement block
%type <node> expression logical_or logical_and
%type <node> equality relational additive
%type <node> multiplicative unary primary

%type <dtype> type

%nonassoc LOWER_THAN_ELSE
%nonassoc TOK_ELSE

%start program

%%

program:
    statement_list
    {
        $$ = ast_create_program();

        $$->data.program.first = $1->data.block.statements;

        ASTNode *current = $$->data.program.first;

        while (current != NULL) {
            $$->data.program.last = current;
            current = current->next;
        }

        $1->data.block.statements = NULL;
        ast_free($1);

        ast_root = $$;
    }
    ;

statement_list:
    /* empty */
    {
        $$ = ast_create_block();
    }
    | statement_list statement
    {
        ast_add_child($1, $2);
        $$ = $1;
    }
    ;

statement:
      declaration      { $$ = $1; }
    | assignment       { $$ = $1; }
    | print_statement  { $$ = $1; }
    | if_statement     { $$ = $1; }
    | while_statement  { $$ = $1; }
    | block            { $$ = $1; }
    ;

declaration:
    type TOK_ID TOK_SEMI
    {
        $$ = ast_create_declaration($1, $2);
    }
    ;

type:
      TOK_INT   { $$ = TYPE_INT; }
    | TOK_FLOAT { $$ = TYPE_FLOAT; }
    | TOK_BOOL  { $$ = TYPE_BOOL; }
    ;

assignment:
    TOK_ID TOK_ASSIGN expression TOK_SEMI
    {
        $$ = ast_create_assignment($1, $3);
    }
    ;

print_statement:
    TOK_PRINT expression TOK_SEMI
    {
        $$ = ast_create_print($2);
    }
    ;

if_statement:
      TOK_IF TOK_LPAREN expression TOK_RPAREN statement
      %prec LOWER_THAN_ELSE
    {
        $$ = ast_create_if($3, $5, NULL);
    }
    | TOK_IF TOK_LPAREN expression TOK_RPAREN statement TOK_ELSE statement
    {
        $$ = ast_create_if($3, $5, $7);
    }
    ;

while_statement:
    TOK_WHILE TOK_LPAREN expression TOK_RPAREN statement
    {
        $$ = ast_create_while($3, $5);
    }
    ;

block:
    TOK_LBRACE statement_list TOK_RBRACE
    {
        $$ = $2;
    }
    ;

expression:
    logical_or
    {
        $$ = $1;
    }
    ;

logical_or:
      logical_and
    {
        $$ = $1;
    }
    | logical_or TOK_OR logical_and
    {
        $$ = ast_create_binary(OP_OR, $1, $3);
    }
    ;

logical_and:
      equality
    {
        $$ = $1;
    }
    | logical_and TOK_AND equality
    {
        $$ = ast_create_binary(OP_AND, $1, $3);
    }
    ;

equality:
      relational
    {
        $$ = $1;
    }
    | equality TOK_EQ relational
    {
        $$ = ast_create_binary(OP_EQ, $1, $3);
    }
    | equality TOK_NE relational
    {
        $$ = ast_create_binary(OP_NE, $1, $3);
    }
    ;

relational:
      additive
    {
        $$ = $1;
    }
    | relational TOK_LT additive
    {
        $$ = ast_create_binary(OP_LT, $1, $3);
    }
    | relational TOK_GT additive
    {
        $$ = ast_create_binary(OP_GT, $1, $3);
    }
    | relational TOK_LE additive
    {
        $$ = ast_create_binary(OP_LE, $1, $3);
    }
    | relational TOK_GE additive
    {
        $$ = ast_create_binary(OP_GE, $1, $3);
    }
    ;

additive:
      multiplicative
    {
        $$ = $1;
    }
    | additive TOK_PLUS multiplicative
    {
        $$ = ast_create_binary(OP_ADD, $1, $3);
    }
    | additive TOK_MINUS multiplicative
    {
        $$ = ast_create_binary(OP_SUB, $1, $3);
    }
    ;

multiplicative:
      unary
    {
        $$ = $1;
    }
    | multiplicative TOK_STAR unary
    {
        $$ = ast_create_binary(OP_MUL, $1, $3);
    }
    | multiplicative TOK_SLASH unary
    {
        $$ = ast_create_binary(OP_DIV, $1, $3);
    }
    | multiplicative TOK_PERCENT unary
    {
        $$ = ast_create_binary(OP_MOD, $1, $3);
    }
    ;

unary:
      primary
    {
        $$ = $1;
    }
    | TOK_NOT unary
    {
        $$ = ast_create_unary(OP_NOT, $2);
    }
    | TOK_MINUS unary
    {
        $$ = ast_create_unary(OP_NEG, $2);
    }
    ;

primary:
      TOK_INTLIT
    {
        $$ = ast_create_int_literal((int)strtol($1, NULL, 10));
        free($1);
    }
    | TOK_FLOATLIT
    {
        $$ = ast_create_float_literal(strtod($1, NULL));
        free($1);
    }
    | TOK_TRUE
    {
        $$ = ast_create_bool_literal(1);
    }
    | TOK_FALSE
    {
        $$ = ast_create_bool_literal(0);
    }
    | TOK_ID
    {
        $$ = ast_create_identifier($1);
    }
    | TOK_LPAREN expression TOK_RPAREN
    {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
}
