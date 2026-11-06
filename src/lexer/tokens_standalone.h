/*
 * tokens_standalone.h - token codes used ONLY while the lexer is built on its own
 * (make lexer_test). Once the Bison parser exists, the same TOK_* names come
 * from Bison's generated header (parser.tab.h) and this file is not used.
 */
#ifndef TOKENS_STANDALONE_H
#define TOKENS_STANDALONE_H

enum {
    TOK_INT = 258, TOK_FLOAT, TOK_BOOL,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_PRINT,
    TOK_TRUE, TOK_FALSE,
    TOK_ID, TOK_INTLIT, TOK_FLOATLIT,
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PERCENT,
    TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_EQ, TOK_NE,
    TOK_AND, TOK_OR, TOK_NOT, TOK_ASSIGN,
    TOK_LBRACE, TOK_RBRACE, TOK_LPAREN, TOK_RPAREN, TOK_SEMI
};

/* The value a token carries to the parser (names and literal text). */
typedef union { char *str; } YYSTYPE;
extern YYSTYPE yylval;

#endif
