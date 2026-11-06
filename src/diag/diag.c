/* diag.c - token log, error log and JSON string helper. */
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "diag.h"

#define MAX_ERRORS 200   /* stop recording after this many, to keep output readable */

TokenRec *g_tokens = NULL;
int g_ntokens = 0;
static int tokens_cap = 0;

ErrorRec *g_errors = NULL;
int g_nerrors = 0;
static int errors_cap = 0;

void diag_token(const char *type, const char *lexeme, int line, int col) {
    if (g_ntokens == tokens_cap) {
        tokens_cap = tokens_cap ? tokens_cap * 2 : 128;
        g_tokens = realloc(g_tokens, tokens_cap * sizeof(TokenRec));
        if (!g_tokens) { fprintf(stderr, "out of memory\n"); exit(2); }
    }
    g_tokens[g_ntokens].type = type;
    g_tokens[g_ntokens].lexeme = strdup(lexeme);
    g_tokens[g_ntokens].line = line;
    g_tokens[g_ntokens].col = col;
    g_ntokens++;
}

void diag_error(const char *phase, const char *category, int line, const char *fmt, ...) {
    if (g_nerrors >= MAX_ERRORS) return;
    if (g_nerrors == errors_cap) {
        errors_cap = errors_cap ? errors_cap * 2 : 16;
        g_errors = realloc(g_errors, errors_cap * sizeof(ErrorRec));
        if (!g_errors) { fprintf(stderr, "out of memory\n"); exit(2); }
    }
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);

    g_errors[g_nerrors].phase = phase;
    g_errors[g_nerrors].category = category;
    g_errors[g_nerrors].line = line;
    g_errors[g_nerrors].message = strdup(buf);
    g_nerrors++;
}

int diag_count(const char *phase) {
    int n = 0;
    for (int i = 0; i < g_nerrors; i++)
        if (strcmp(g_errors[i].phase, phase) == 0) n++;
    return n;
}

void json_string(FILE *out, const char *s) {
    fputc('"', out);
    for (const unsigned char *p = (const unsigned char *)s; *p; p++) {
        switch (*p) {
            case '"':  fputs("\\\"", out); break;
            case '\\': fputs("\\\\", out); break;
            case '\n': fputs("\\n", out);  break;
            case '\r': fputs("\\r", out);  break;
            case '\t': fputs("\\t", out);  break;
            default:
                if (*p < 0x20) fprintf(out, "\\u%04x", *p);
                else fputc(*p, out);
        }
    }
    fputc('"', out);
}
