#pragma once

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>

typedef struct {
    char* name;
    double value;
} SymbolTableEntry;

typedef struct {
    SymbolTableEntry* entries;
    int size;
    int capacity;
} SymbolTable;

SymbolTable* symbol_table_create();
void symbol_table_add(SymbolTable* table, const char* name, double value);
double symbol_table_get(SymbolTable* table, const char* name);
void symbol_table_free(SymbolTable* table);

#endif