
# Lexora Compiler Makefile

CC     = gcc
CFLAGS = -Wall -Wextra -g -Isrc/diag -Isrc/lexer -Isrc/parser -Isrc/ast

FLEX  ?= win_flex
BISON ?= win_bison

LEXER_TEST = lexer_test
LEXORA     = lexora

DIAG_SRC = src/diag/diag.c
AST_SRC  = src/ast/ast.c

.PHONY: all lexer_test parser test clean

# Build lexer test and complete compiler
all: $(LEXER_TEST) $(LEXORA)

# Generate Bison parser files
src/parser/parser.tab.c src/parser/parser.tab.h &: src/parser/parser.y
	$(BISON) -d -o src/parser/parser.tab.c src/parser/parser.y

# Generate Flex scanner
src/lexer/lex.yy.c: src/lexer/lexer.l src/parser/parser.tab.h
	$(FLEX) -o $@ $<

# Build standalone lexer
$(LEXER_TEST): src/lexer/lex.yy.c src/lexer/lexer_main.c $(DIAG_SRC)
	$(CC) $(CFLAGS) -DLEXER_ONLY -o $@ $^

# Build complete Lexora compiler
$(LEXORA): src/parser/parser.tab.c src/lexer/lex.yy.c src/parser/parser_main.c $(DIAG_SRC) $(AST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Parser shortcut
parser: $(LEXORA)

# Run only lexer tests having expected output files
test: $(LEXER_TEST)
	@pass=0; fail=0; \
	for exp in tests/*/*.tokens.expected; do \
	  f=$${exp%.tokens.expected}.mc; \
	  if ./$(LEXER_TEST) $$f | diff -q --strip-trailing-cr - $$exp > /dev/null; then \
	    echo "PASS  $$f"; pass=$$((pass+1)); \
	  else \
	    echo "FAIL  $$f"; fail=$$((fail+1)); \
	  fi; \
	done; \
	echo "$$pass passed, $$fail failed"; [ $$fail -eq 0 ]

# Clean generated files and executables
clean:
	$(RM) src/lexer/lex.yy.c
	$(RM) src/parser/parser.tab.c src/parser/parser.tab.h
	$(RM) $(LEXER_TEST) $(LEXER_TEST).exe
	$(RM) $(LEXORA) $(LEXORA).exe
