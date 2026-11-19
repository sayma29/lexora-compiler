
#ifndef LEXORA_SYMBOL_TABLE_H
#define LEXORA_SYMBOL_TABLE_H

#include "ast.h"

/* Information about one declared variable */
typedef struct Symbol {
    char *name;
    DataType type;
    int line_declared;

    struct Symbol *next;
} Symbol;

/* Represents one scope */
typedef struct Scope {
    int scope_id;
    struct Scope *parent;

    Symbol *symbols;
    struct Scope *next;

} Scope;

/* Symbol table manager */
typedef struct SymbolTable {
    Scope *current_scope;
    int next_scope_id;
} SymbolTable;

/* Symbol table functions */
SymbolTable *symbol_table_create(void);

void symbol_table_enter_scope(SymbolTable *table);
void symbol_table_exit_scope(SymbolTable *table);

int symbol_table_insert(SymbolTable *table,
                        const char *name,
                        DataType type,
                        int line);

Symbol *symbol_table_lookup(SymbolTable *table,
                            const char *name);

void symbol_table_print(SymbolTable *table);

void symbol_table_free(SymbolTable *table);

#endif
