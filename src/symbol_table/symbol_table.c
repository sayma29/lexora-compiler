
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

/* Duplicate a string */
static char *copy_string(const char *str)
{
    if (str == NULL)
        return NULL;

    char *copy = malloc(strlen(str) + 1);

    if (copy == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(copy, str);
    return copy;
}

/* Get data type name */
static const char *get_type_name(DataType type)
{
    switch (type) {
        case TYPE_INT:   return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOL:  return "bool";
        default:         return "unknown";
    }
}

/* Create a new scope */
static Scope *create_scope(int id, Scope *parent)
{
    Scope *scope = calloc(1, sizeof(Scope));

    if (scope == NULL) {
        fprintf(stderr, "Error: Scope allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    scope->scope_id = id;
    scope->parent = parent;
    scope->symbols = NULL;
    scope->next = NULL;

    return scope;
}

/* Create the symbol table */
SymbolTable *symbol_table_create(void)
{
    SymbolTable *table = calloc(1, sizeof(SymbolTable));

    if (table == NULL) {
        fprintf(stderr, "Error: Symbol table allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    table->next_scope_id = 1;
    table->current_scope = create_scope(0, NULL);

    return table;
}

/* Enter a new nested scope */
void symbol_table_enter_scope(SymbolTable *table)
{
    if (table == NULL)
        return;

    Scope *new_scope = create_scope(
        table->next_scope_id++,
        table->current_scope
    );

    table->current_scope = new_scope;
}

/* Exit the current scope */
void symbol_table_exit_scope(SymbolTable *table)
{
    if (table == NULL || table->current_scope == NULL)
        return;

    /* Do not remove the global scope */
    if (table->current_scope->parent == NULL)
        return;

    Scope *old_scope = table->current_scope;

    table->current_scope = old_scope->parent;

    Symbol *symbol = old_scope->symbols;

    while (symbol != NULL) {
        Symbol *next_symbol = symbol->next;

        free(symbol->name);
        free(symbol);

        symbol = next_symbol;
    }

    free(old_scope);
}

/* Insert a variable into the current scope */
int symbol_table_insert(SymbolTable *table,
                        const char *name,
                        DataType type,
                        int line)
{
    if (table == NULL || table->current_scope == NULL || name == NULL)
        return 0;

    Scope *scope = table->current_scope;

    /* Check redeclaration in the same scope */
    Symbol *current = scope->symbols;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return 0;

        current = current->next;
    }

    /* Create a new symbol */
    Symbol *new_symbol = calloc(1, sizeof(Symbol));

    if (new_symbol == NULL) {
        fprintf(stderr, "Error: Symbol allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_symbol->name = copy_string(name);
    new_symbol->type = type;
    new_symbol->line_declared = line;

    /* Insert at the beginning of the symbol list */
    new_symbol->next = scope->symbols;
    scope->symbols = new_symbol;

    return 1;
}

/* Search for a variable in current and parent scopes */
Symbol *symbol_table_lookup(SymbolTable *table,
                            const char *name)
{
    if (table == NULL || name == NULL)
        return NULL;

    Scope *scope = table->current_scope;

    while (scope != NULL) {

        Symbol *symbol = scope->symbols;

        while (symbol != NULL) {
            if (strcmp(symbol->name, name) == 0)
                return symbol;

            symbol = symbol->next;
        }

        /* Search in the parent scope */
        scope = scope->parent;
    }

    return NULL;
}

/* Print scopes from outermost to innermost */
static void print_scope(Scope *scope)
{
    if (scope == NULL)
        return;

    print_scope(scope->parent);

    printf("\nScope ID: %d\n", scope->scope_id);
    printf("-------------------------\n");

    Symbol *symbol = scope->symbols;

    if (symbol == NULL) {
        printf("No variables declared.\n");
    }

    while (symbol != NULL) {
        printf("Name: %s | Type: %s | Line: %d\n",
               symbol->name,
               get_type_name(symbol->type),
               symbol->line_declared);

        symbol = symbol->next;
    }
}

/* Display the symbol table */
void symbol_table_print(SymbolTable *table)
{
    if (table == NULL)
        return;

    printf("\n========== SYMBOL TABLE ==========\n");

    print_scope(table->current_scope);

    printf("\n==================================\n");
}

/* Free all remaining scopes and symbols */
void symbol_table_free(SymbolTable *table)
{
    if (table == NULL)
        return;

    while (table->current_scope != NULL) {

        Scope *scope = table->current_scope;
        table->current_scope = scope->parent;

        Symbol *symbol = scope->symbols;

        while (symbol != NULL) {
            Symbol *next_symbol = symbol->next;

            free(symbol->name);
            free(symbol);

            symbol = next_symbol;
        }

        free(scope);
    }

    free(table);
}
