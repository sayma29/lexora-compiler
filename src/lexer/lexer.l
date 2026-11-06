/*
 * lexer.l - Lexical analyzer for Lexora (Flex / win_flex).
 *
 * Reads source text and turns it into tokens. For every token it
 *   1. records the token (type, text, line, column) with diag_token(), and
 *   2. returns a TOK_* code to the parser.
 * Comments and whitespace are discarded. Anything that is not a valid token
 * is logged as a lexical error with its line number, and scanning continues.
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
#include "parser.tab.h"
#endif

static int col = 1;           /* column where the NEXT character starts */
static int tok_col = 1;       /* column where the CURRENT token starts  */
static int comment_start = 0; /* line where an open block comment began */

/* Runs before every rule: remember where this match starts, then advance. */
#define YY_USER_ACTION { tok_col = col; col += yyleng; }

/* Log a valid token and hand its code to the parser. */
#define EMIT(TYPE, CODE) \
    do { diag_token(TYPE, yytext, yylineno, tok_col); return CODE; } while (0)

/* Log an invalid token and keep scanning (no token is passed to the parser). */
#define INVALID(MSG) \
    do { diag_token("INVALID", yytext, yylineno, tok_col); \
         diag_error(PHASE_LEXICAL, "invalid_token", yylineno, MSG " '%s'", yytext); } while (0)
%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%x COMMENT

%%

 /* ---- comments and whitespace: discarded, never tokenized ---- */
"//"[^\n]*              { /* single-line comment */ }
"/*"                    { comment_start = yylineno; BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>\n             { col = 1; }
<COMMENT>.              { /* inside block comment */ }
<COMMENT><<EOF>>        {
                          diag_error(PHASE_LEXICAL, "unterminated_comment", comment_start,
                                     "Unterminated block comment (opened here, never closed with */)");
                          BEGIN(INITIAL);
                          return 0;
                        }

[ \t\r]+                { /* whitespace */ }
\n                      { col = 1; }

 /* ---- keywords (listed before identifiers; longest match still wins) ---- */
"int"                   { EMIT("KEYWORD", TOK_INT); }
"float"                 { EMIT("KEYWORD", TOK_FLOAT); }
"bool"                  { EMIT("KEYWORD", TOK_BOOL); }
"if"                    { EMIT("KEYWORD", TOK_IF); }
"else"                  { EMIT("KEYWORD", TOK_ELSE); }
"while"                 { EMIT("KEYWORD", TOK_WHILE); }
"print"                 { EMIT("KEYWORD", TOK_PRINT); }
"true"                  { EMIT("BOOL_LITERAL", TOK_TRUE); }
"false"                 { EMIT("BOOL_LITERAL", TOK_FALSE); }

 /* ---- identifiers: letter or underscore, then letters, digits, underscores ---- */
{LETTER}({LETTER}|{DIGIT})* {
                          yylval.str = strdup(yytext);
                          EMIT("IDENTIFIER", TOK_ID);
                        }

 /* ---- numbers ---- */
{DIGIT}+"."{DIGIT}+     { yylval.str = strdup(yytext); EMIT("FLOAT_LITERAL", TOK_FLOATLIT); }
{DIGIT}+                { yylval.str = strdup(yytext); EMIT("INT_LITERAL", TOK_INTLIT); }

 /* malformed numbers: these are longer matches than the valid rules above */
{DIGIT}+{LETTER}({LETTER}|{DIGIT})* { INVALID("Invalid identifier (cannot start with a digit)"); }
{DIGIT}+"."             { INVALID("Malformed number (digits needed after the decimal point)"); }
"."{DIGIT}+             { INVALID("Malformed number (digits needed before the decimal point)"); }

 /* ---- operators: two-character ones first so <= is not < followed by = ---- */
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

 /* ---- delimiters ---- */
"{"                     { EMIT("DELIMITER", TOK_LBRACE); }
"}"                     { EMIT("DELIMITER", TOK_RBRACE); }
"("                     { EMIT("DELIMITER", TOK_LPAREN); }
")"                     { EMIT("DELIMITER", TOK_RPAREN); }
";"                     { EMIT("DELIMITER", TOK_SEMI); }

 /* ---- invalid input ---- */
"&"                     { INVALID("Invalid operator (did you mean '&&'?)"); }
"|"                     { INVALID("Invalid operator (did you mean '||'?)"); }
.                       { INVALID("Invalid character"); }

%%
