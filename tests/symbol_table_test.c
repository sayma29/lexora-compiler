
#include <stdio.h>
#include "symbol_table.h"

int main(void)
{
    SymbolTable *table = symbol_table_create();

    printf("=== SYMBOL TABLE TEST ===\n");

    /* Test 1: Insert variables into global scope */
    printf("\nTest 1: Global Scope\n");

    printf("Insert x: %s\n",
           symbol_table_insert(table, "x", TYPE_INT, 1)
               ? "PASS" : "FAIL");

    printf("Insert y: %s\n",
           symbol_table_insert(table, "y", TYPE_FLOAT, 2)
               ? "PASS" : "FAIL");

    /* Test 2: Detect redeclaration */
    printf("\nTest 2: Redeclaration Check\n");

    printf("Redeclare x: %s\n",
           !symbol_table_insert(table, "x", TYPE_INT, 3)
               ? "PASS" : "FAIL");

    /* Test 3: Lookup variable */
    printf("\nTest 3: Variable Lookup\n");

    Symbol *found = symbol_table_lookup(table, "x");

    printf("Find x: %s\n",
           found != NULL && found->type == TYPE_INT
               ? "PASS" : "FAIL");

    /* Test 4: Nested scope */
    printf("\nTest 4: Nested Scope\n");

    symbol_table_enter_scope(table);

    printf("Find parent variable x: %s\n",
           symbol_table_lookup(table, "x") != NULL
               ? "PASS" : "FAIL");

    printf("Insert local variable z: %s\n",
           symbol_table_insert(table, "z", TYPE_BOOL, 5)
               ? "PASS" : "FAIL");

    /* Test 5: Exit nested scope */
    printf("\nTest 5: Scope Exit\n");

    symbol_table_exit_scope(table);

    printf("Find global x: %s\n",
           symbol_table_lookup(table, "x") != NULL
               ? "PASS" : "FAIL");

    printf("Find local z: %s\n",
           symbol_table_lookup(table, "z") == NULL
               ? "PASS" : "FAIL");

    /* Display symbol table */
    symbol_table_print(table);

    symbol_table_free(table);

    printf("\n=== TEST COMPLETED ===\n");

    return 0;
}
