# Lexora Makefile
#
# Tool names are variables so this works with either setup:
#   win_flex / win_bison  (win_flex_bison zip)  -> just run `make`
#   flex / bison          (MSYS2, Linux)        -> run `make FLEX=flex BISON=bison`

CC     = gcc
CFLAGS = -Wall -Wextra -g -Isrc/diag -Isrc/lexer
FLEX  ?= win_flex

LEXER_TEST = lexer_test
DIAG_SRC   = src/diag/diag.c

.PHONY: all lexer_test test clean

all: $(LEXER_TEST)

# 1. Flex turns lexer.l into C code (generated file, ignored by git)
src/lexer/lex.yy.c: src/lexer/lexer.l
	$(FLEX) -o $@ $<

# 2. Compile the lexer on its own, with the small test driver
$(LEXER_TEST): src/lexer/lex.yy.c src/lexer/lexer_main.c $(DIAG_SRC)
	$(CC) $(CFLAGS) -DLEXER_ONLY -o $@ $^

# Run every tests/*/*.mc program and compare against its .tokens.expected file
test: $(LEXER_TEST)
	@pass=0; fail=0; \
	for f in tests/*/*.mc; do \
	  exp=$${f%.mc}.tokens.expected; \
	  if ./$(LEXER_TEST) $$f | diff -q --strip-trailing-cr - $$exp > /dev/null; then \
	    echo "PASS  $$f"; pass=$$((pass+1)); \
	  else \
	    echo "FAIL  $$f"; fail=$$((fail+1)); \
	  fi; \
	done; \
	echo "$$pass passed, $$fail failed"; [ $$fail -eq 0 ]

clean:
	$(RM) src/lexer/lex.yy.c $(LEXER_TEST) $(LEXER_TEST).exe
