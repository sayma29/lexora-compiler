
/*
 * lexer.l - Lexical analyzer for Lexora (Flex / win_flex).
 */

%option noyywrap noinput nounput nounistd never-interactive yylineno

%{
#include <stdlib.h>
#include <string.h>
#include "diag.h"

#ifdef LEXER_ONLY
#include "tokens_standalone.h"
YYSTYPE yylval;
#else
#include "ast.h"
#include "parser.tab.h"
#endif

static int col = 1;
static int tok_col = 1;
static int comment_start = 0;

#ifdef LEXER_ONLY
#define YY_USER_ACTION { \
    tok_col = col; \
    col += yyleng; \
}
#else
#define YY_USER_ACTION { \
    tok_col = col; \
    yylloc.first_line = yylineno; \
    yylloc.last_line = yylineno; \
    yylloc.first_column = col; \
    yylloc.last_column = col + yyleng; \
    col += yyleng; \
}
#endif

#define EMIT(TYPE, CODE) \
    do { \
        diag_token(TYPE, yytext, yylineno, tok_col); \
        return CODE; \
    } while (0)

#define INVALID(MSG) \
    do { \
        diag_token("INVALID", yytext, yylineno, tok_col); \
        diag_error(PHASE_LEXICAL, "invalid_token", yylineno, \
                   MSG " '%s'", yytext); \
    } while (0)

%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%x COMMENT

%%

"//"[^\n]*              { /* Single-line comment */ }
"/*"                    { comment_start = yylineno; BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>\n             { col = 1; }
<COMMENT>.              { /* Inside block comment */ }

<COMMENT><<EOF>>        {
    diag_error(PHASE_LEXICAL, "unterminated_comment",
               comment_start,
              "Unterminated block comment (opened here, never closed with */)");
    BEGIN(INITIAL);
    return 0;
}

[ \t\r]+                { /* Whitespace */ }
\n                      { col = 1; }

"int"                   { EMIT("KEYWORD", TOK_INT); }
"float"                 { EMIT("KEYWORD", TOK_FLOAT); }
"bool"                  { EMIT("KEYWORD", TOK_BOOL); }
"if"                    { EMIT("KEYWORD", TOK_IF); }
"else"                  { EMIT("KEYWORD", TOK_ELSE); }
"while"                 { EMIT("KEYWORD", TOK_WHILE); }
"print"                 { EMIT("KEYWORD", TOK_PRINT); }

"true"                  { EMIT("BOOL_LITERAL", TOK_TRUE); }
"false"                 { EMIT("BOOL_LITERAL", TOK_FALSE); }

{LETTER}({LETTER}|{DIGIT})* {
    yylval.str = strdup(yytext);
    EMIT("IDENTIFIER", TOK_ID);
}

{DIGIT}+"."{DIGIT}+     {
    yylval.str = strdup(yytext);
    EMIT("FLOAT_LITERAL", TOK_FLOATLIT);
}

{DIGIT}+                {
    yylval.str = strdup(yytext);
    EMIT("INT_LITERAL", TOK_INTLIT);
}

{DIGIT}+{LETTER}({LETTER}|{DIGIT})* {
    INVALID("Invalid identifier (cannot start with a digit)");
}

{DIGIT}+"."             {
    INVALID("Malformed number (digits needed after the decimal point)");
}

"."{DIGIT}+             {
    INVALID("Malformed number (digits needed after the decimal point)");
}

"<="                    { EMIT("OPERATOR", TOK_LE); }
">="                    { EMIT("OPERATOR", TOK_GE); }
"=="                    { EMIT("OPERATOR", TOK_EQ); }
"!="                    { EMIT("OPERATOR", TOK_NE); }
"&&"                    { EMIT("OPERATOR", TOK_AND); }
"||"                    { EMIT("OPERATOR", TOK_OR); }

"+"                     { EMIT("OPERATOR", TOK_PLUS); }
"-"                     { EMIT("OPERATOR", TOK_MINUS); }
"*"                     { EMIT("OPERATOR", TOK_STAR); }
"/"                     { EMIT("OPERATOR", TOK_SLASH); }
"%"                     { EMIT("OPERATOR", TOK_PERCENT); }
"<"                     { EMIT("OPERATOR", TOK_LT); }
">"                     { EMIT("OPERATOR", TOK_GT); }
"!"                     { EMIT("OPERATOR", TOK_NOT); }
"="                     { EMIT("OPERATOR", TOK_ASSIGN); }

"{"                     { EMIT("DELIMITER", TOK_LBRACE); }
"}"                     { EMIT("DELIMITER", TOK_RBRACE); }
"("                     { EMIT("DELIMITER", TOK_LPAREN); }
")"                     { EMIT("DELIMITER", TOK_RPAREN); }
";"                     { EMIT("DELIMITER", TOK_SEMI); }

"&"                     { INVALID("Invalid operator (did you mean '&&'?)"); }
"|"                     { INVALID("Invalid operator (did you mean '||'?)"); }
.                       { INVALID("Invalid character"); }

%%
