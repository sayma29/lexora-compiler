
#ifndef LEXORA_AST_H
#define LEXORA_AST_H

typedef enum {
    AST_PROGRAM,
    AST_BLOCK,
    AST_DECLARATION,
    AST_ASSIGNMENT,
    AST_PRINT,
    AST_IF,
    AST_WHILE,
    AST_BINARY,
    AST_UNARY,
    AST_IDENTIFIER,
    AST_INT_LITERAL,
    AST_FLOAT_LITERAL,
    AST_BOOL_LITERAL
} ASTNodeType;

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_UNKNOWN
} DataType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_EQ,
    OP_NE,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_NEG
} Operator;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNodeType type;

    /* Source line number */
    int line;

    union {
        struct {
            ASTNode *first;
            ASTNode *last;
        } program;

        struct {
            ASTNode *statements;
        } block;

        struct {
            char *name;
            DataType data_type;
        } declaration;

        struct {
            char *name;
            ASTNode *value;
        } assignment;

        struct {
            ASTNode *expression;
        } print_stmt;

        struct {
            ASTNode *condition;
            ASTNode *then_branch;
            ASTNode *else_branch;
        } if_stmt;

        struct {
            ASTNode *condition;
            ASTNode *body;
        } while_stmt;

        struct {
            Operator op;
            ASTNode *left;
            ASTNode *right;
        } binary;

        struct {
            Operator op;
            ASTNode *operand;
        } unary;

        struct {
            char *name;
        } identifier;

        struct {
            int value;
        } int_literal;

        struct {
            double value;
        } float_literal;

        struct {
            int value;
        } bool_literal;
    } data;

    ASTNode *next;
};

ASTNode *ast_create_program(void);
ASTNode *ast_create_block(void);
ASTNode *ast_create_declaration(DataType type, char *name);
ASTNode *ast_create_assignment(char *name, ASTNode *value);
ASTNode *ast_create_print(ASTNode *expression);
ASTNode *ast_create_if(ASTNode *condition, ASTNode *then_branch,
                       ASTNode *else_branch);
ASTNode *ast_create_while(ASTNode *condition, ASTNode *body);
ASTNode *ast_create_binary(Operator op, ASTNode *left, ASTNode *right);
ASTNode *ast_create_unary(Operator op, ASTNode *operand);
ASTNode *ast_create_identifier(char *name);
ASTNode *ast_create_int_literal(int value);
ASTNode *ast_create_float_literal(double value);
ASTNode *ast_create_bool_literal(int value);

void ast_add_child(ASTNode *parent, ASTNode *child);
void ast_print(ASTNode *node, int depth);
void ast_free(ASTNode *node);

#endif
