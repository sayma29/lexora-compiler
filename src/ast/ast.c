
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/* Create an empty AST node */
static ASTNode *ast_new_node(ASTNodeType type)
{
    ASTNode *node = calloc(1, sizeof(ASTNode));

    if (node == NULL) {
        fprintf(stderr, "Error: AST memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->type = type;
    return node;
}

/* Create program node */
ASTNode *ast_create_program(void)
{
    return ast_new_node(AST_PROGRAM);
}

/* Create block node */
ASTNode *ast_create_block(void)
{
    return ast_new_node(AST_BLOCK);
}

/* Create declaration node */
ASTNode *ast_create_declaration(DataType type, char *name)
{
    ASTNode *node = ast_new_node(AST_DECLARATION);

    node->data.declaration.data_type = type;
    node->data.declaration.name = name;

    return node;
}

/* Create assignment node */
ASTNode *ast_create_assignment(char *name, ASTNode *value)
{
    ASTNode *node = ast_new_node(AST_ASSIGNMENT);

    node->data.assignment.name = name;
    node->data.assignment.value = value;

    return node;
}

/* Create print node */
ASTNode *ast_create_print(ASTNode *expression)
{
    ASTNode *node = ast_new_node(AST_PRINT);

    node->data.print_stmt.expression = expression;

    return node;
}

/* Create if / if-else node */
ASTNode *ast_create_if(ASTNode *condition,
                       ASTNode *then_branch,
                       ASTNode *else_branch)
{
    ASTNode *node = ast_new_node(AST_IF);

    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_branch = then_branch;
    node->data.if_stmt.else_branch = else_branch;

    return node;
}

/* Create while node */
ASTNode *ast_create_while(ASTNode *condition, ASTNode *body)
{
    ASTNode *node = ast_new_node(AST_WHILE);

    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;

    return node;
}

/* Create binary expression node */
ASTNode *ast_create_binary(Operator op,
                           ASTNode *left,
                           ASTNode *right)
{
    ASTNode *node = ast_new_node(AST_BINARY);

    node->data.binary.op = op;
    node->data.binary.left = left;
    node->data.binary.right = right;

    return node;
}

/* Create unary expression node */
ASTNode *ast_create_unary(Operator op, ASTNode *operand)
{
    ASTNode *node = ast_new_node(AST_UNARY);

    node->data.unary.op = op;
    node->data.unary.operand = operand;

    return node;
}

/* Create identifier node */
ASTNode *ast_create_identifier(char *name)
{
    ASTNode *node = ast_new_node(AST_IDENTIFIER);

    node->data.identifier.name = name;

    return node;
}

/* Create integer literal node */
ASTNode *ast_create_int_literal(int value)
{
    ASTNode *node = ast_new_node(AST_INT_LITERAL);

    node->data.int_literal.value = value;

    return node;
}

/* Create float literal node */
ASTNode *ast_create_float_literal(double value)
{
    ASTNode *node = ast_new_node(AST_FLOAT_LITERAL);

    node->data.float_literal.value = value;

    return node;
}

/* Create boolean literal node */
ASTNode *ast_create_bool_literal(int value)
{
    ASTNode *node = ast_new_node(AST_BOOL_LITERAL);

    node->data.bool_literal.value = value;

    return node;
}

/* Add a statement to a program or block */
void ast_add_child(ASTNode *parent, ASTNode *child)
{
    if (parent == NULL || child == NULL)
        return;

    if (parent->type == AST_PROGRAM) {
        if (parent->data.program.first == NULL) {
            parent->data.program.first = child;
        } else {
            parent->data.program.last->next = child;
        }

        parent->data.program.last = child;
    }
    else if (parent->type == AST_BLOCK) {
        ASTNode **current = &parent->data.block.statements;

        while (*current != NULL)
            current = &(*current)->next;

        *current = child;
    }
}

/* Print indentation */
static void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
}

/* Get data type name */
static const char *type_name(DataType type)
{
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOL: return "bool";
        default: return "unknown";
    }
}

/* Get operator name */
static const char *operator_name(Operator op)
{
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_LT: return "<";
        case OP_GT: return ">";
        case OP_LE: return "<=";
        case OP_GE: return ">=";
        case OP_EQ: return "==";
        case OP_NE: return "!=";
        case OP_AND: return "&&";
        case OP_OR: return "||";
        case OP_NOT: return "!";
        case OP_NEG: return "-";
        default: return "?";
    }
}

/* Print AST for debugging */
void ast_print(ASTNode *node, int depth)
{
    if (node == NULL)
        return;

    print_indent(depth);

    switch (node->type) {

        case AST_PROGRAM:
            printf("PROGRAM\n");
            ast_print(node->data.program.first, depth + 1);
            break;

        case AST_BLOCK:
            printf("BLOCK\n");
            ast_print(node->data.block.statements, depth + 1);
            break;

        case AST_DECLARATION:
            printf("DECLARATION: %s %s\n",
                   type_name(node->data.declaration.data_type),
                   node->data.declaration.name);
            break;

        case AST_ASSIGNMENT:
            printf("ASSIGNMENT: %s\n",
                   node->data.assignment.name);
            ast_print(node->data.assignment.value, depth + 1);
            break;

        case AST_PRINT:
            printf("PRINT\n");
            ast_print(node->data.print_stmt.expression, depth + 1);
            break;

        case AST_IF:
            printf("IF\n");
            print_indent(depth + 1);
            printf("CONDITION:\n");
            ast_print(node->data.if_stmt.condition, depth + 2);
            print_indent(depth + 1);
            printf("THEN:\n");
            ast_print(node->data.if_stmt.then_branch, depth + 2);

            if (node->data.if_stmt.else_branch != NULL) {
                print_indent(depth + 1);
                printf("ELSE:\n");
                ast_print(node->data.if_stmt.else_branch, depth + 2);
            }
            break;

        case AST_WHILE:
            printf("WHILE\n");
            print_indent(depth + 1);
            printf("CONDITION:\n");
            ast_print(node->data.while_stmt.condition, depth + 2);
            print_indent(depth + 1);
            printf("BODY:\n");
            ast_print(node->data.while_stmt.body, depth + 2);
            break;

        case AST_BINARY:
            printf("BINARY: %s\n",
                   operator_name(node->data.binary.op));
            ast_print(node->data.binary.left, depth + 1);
            ast_print(node->data.binary.right, depth + 1);
            break;

        case AST_UNARY:
            printf("UNARY: %s\n",
                   operator_name(node->data.unary.op));
            ast_print(node->data.unary.operand, depth + 1);
            break;

        case AST_IDENTIFIER:
            printf("IDENTIFIER: %s\n",
                   node->data.identifier.name);
            break;

        case AST_INT_LITERAL:
            printf("INT_LITERAL: %d\n",
                   node->data.int_literal.value);
            break;

        case AST_FLOAT_LITERAL:
            printf("FLOAT_LITERAL: %g\n",
                   node->data.float_literal.value);
            break;

        case AST_BOOL_LITERAL:
            printf("BOOL_LITERAL: %s\n",
                   node->data.bool_literal.value ? "true" : "false");
            break;
    }

    ast_print(node->next, depth);
}

/* Free AST memory */
void ast_free(ASTNode *node)
{
    if (node == NULL)
        return;

    ASTNode *next = node->next;

    switch (node->type) {

        case AST_PROGRAM:
            ast_free(node->data.program.first);
            break;

        case AST_BLOCK:
            ast_free(node->data.block.statements);
            break;

        case AST_DECLARATION:
            free(node->data.declaration.name);
            break;

        case AST_ASSIGNMENT:
            free(node->data.assignment.name);
            ast_free(node->data.assignment.value);
            break;

        case AST_PRINT:
            ast_free(node->data.print_stmt.expression);
            break;

        case AST_IF:
            ast_free(node->data.if_stmt.condition);
            ast_free(node->data.if_stmt.then_branch);
            ast_free(node->data.if_stmt.else_branch);
            break;

        case AST_WHILE:
            ast_free(node->data.while_stmt.condition);
            ast_free(node->data.while_stmt.body);
            break;

        case AST_BINARY:
            ast_free(node->data.binary.left);
            ast_free(node->data.binary.right);
            break;

        case AST_UNARY:
            ast_free(node->data.unary.operand);
            break;

        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;

        default:
            break;
    }

    free(node);
    ast_free(next);
}
