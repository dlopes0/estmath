#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evaluator.h"
#include "symbol_table.h"

SymbolTable* symbol_table_create() 
{
    SymbolTable* table = malloc(sizeof(SymbolTable));
    table->entries = malloc(sizeof(SymbolTableEntry) * 10);  // Initial capacity
    table->size = 0;
    table->capacity = 10;

    // Add predefined variables
    symbol_table_add(table, "pi", 3.14159265358979323846, NULL);
    symbol_table_add(table, "e", 2.71828182845904523536, NULL);

    return table;
}

void symbol_table_add(SymbolTable* table, const char* name, double value, Node* expression) 
{
    // Resize if needed
    if (table->size >= table->capacity)
    {
        table->capacity *= 2;
        table->entries = realloc(table->entries, sizeof(SymbolTableEntry) * table->capacity);
    }

    // Check if variable already exists
    for (int i = 0; i < table->size; i++) 
    {
        if (strcmp(table->entries[i].name, name) == 0)
        {
            table->entries[i].value = value;
            if (table->entries[i].expression) 
            {
                free_ast(table->entries[i].expression); // Free old expression if present
            }
            table->entries[i].expression = expression;
            return;
        }
    }

    // Add new variable
    table->entries[table->size].name = strdup(name);
    table->entries[table->size].value = value;
    table->size++;
}

double symbol_table_get(SymbolTable* table, const char* name) 
{
    for (int i = 0; i < table->size; i++) 
    {
        if (strcmp(table->entries[i].name, name) == 0) 
        {
            if (table->entries[i].expression) 
            {
                // Evaluate the stored expression dynamically
                return evaluate_ast(table->entries[i].expression, table);
            }
            return table->entries[i].value;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not defined\n", name);
    exit(EXIT_FAILURE);
}

void symbol_table_free(SymbolTable* table) 
{
    for (int i = 0; i < table->size; i++) 
    {
        free(table->entries[i].name);
    }
    free(table->entries);
    free(table);
}