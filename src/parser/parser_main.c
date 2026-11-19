
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern FILE *yyin;
extern int yylineno;
extern ASTNode *ast_root;

int yyparse(void);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (yyin == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    yylineno = 1;

    printf("Lexora Compiler - Syntax Analysis\n");
    printf("---------------------------------\n");

    int result = yyparse();

    fclose(yyin);

    if (result == 0)
    {
        printf("\nParsing successful!\n");

        printf("\nAbstract Syntax Tree (AST):\n");
        printf("--------------------------\n");

        ast_print(ast_root, 0);

        ast_free(ast_root);
        ast_root = NULL;

        return 0;
    }
    else
    {
        printf("\nParsing failed due to syntax errors.\n");

        return 1;
    }
}
