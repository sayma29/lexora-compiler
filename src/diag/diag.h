/*
 * diag.h - Diagnostics shared by every compiler phase.
 *
 * Two global logs are kept while compiling:
 *   - the token log   (filled by the lexer, one entry per token)
 *   - the error log   (filled by lexer, parser and semantic analyzer)
 * main.c reads both logs at the end to print the report (text or JSON).
 */
#ifndef DIAG_H
#define DIAG_H

#include <stdio.h>

/* Phase names used in the error log. */
#define PHASE_LEXICAL  "lexical"
#define PHASE_SYNTAX   "syntax"
#define PHASE_SEMANTIC "semantic"

typedef struct {
    const char *type;   /* KEYWORD, IDENTIFIER, INT_LITERAL, ... or INVALID */
    char *lexeme;       /* the exact text matched */
    int line;
    int col;
} TokenRec;

typedef struct {
    const char *phase;     /* PHASE_* */
    const char *category;  /* machine-readable kind, e.g. "undeclared" */
    int line;
    char *message;         /* human-readable description */
} ErrorRec;

extern TokenRec *g_tokens;
extern int g_ntokens;
extern ErrorRec *g_errors;
extern int g_nerrors;

void diag_token(const char *type, const char *lexeme, int line, int col);
void diag_error(const char *phase, const char *category, int line, const char *fmt, ...);
int  diag_count(const char *phase);   /* number of errors logged for a phase */

/* Writes s as a quoted, escaped JSON string. */
void json_string(FILE *out, const char *s);

#endif
