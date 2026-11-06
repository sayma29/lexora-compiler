/*
 * lexer_main.c - test driver that runs ONLY the lexer and prints its results.
 * Build with `make lexer_test`, run with `./lexer_test file.mc`.
 * Later, main.c replaces this and runs every phase.
 */
#include <stdio.h>
#include "diag.h"
#include "tokens_standalone.h"

extern FILE *yyin;
extern int yylex(void);

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror(argv[1]); return 2; }
    }

    while (yylex() != 0) { /* each call scans one token and logs it */ }

    printf("=== TOKENS (%d) ===\n", g_ntokens);
    printf("%-9s %-14s %s\n", "LINE:COL", "TYPE", "LEXEME");
    for (int i = 0; i < g_ntokens; i++) {
        char pos[24];
        snprintf(pos, sizeof pos, "%d:%d", g_tokens[i].line, g_tokens[i].col);
        printf("%-9s %-14s %s\n", pos, g_tokens[i].type, g_tokens[i].lexeme);
    }

    int errors = diag_count(PHASE_LEXICAL);
    printf("\n=== LEXICAL ERRORS (%d) ===\n", errors);
    for (int i = 0; i < g_nerrors; i++)
        printf("Lexical error at line %d: %s\n", g_errors[i].line, g_errors[i].message);

    return errors ? 1 : 0;
}
