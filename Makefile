CXX = g++
CXXFLAGS = -std=c++17 -Wall -I src

FLEX = flex
BISON = bison

all: lexora

lexora:
	@echo "Lexora Compiler Build System Ready!"

clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h lexora.exe