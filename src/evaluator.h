#pragma once

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "symbol_table.h"

double evaluate_ast(Node* node, SymbolTable* symbol_table);

#endif