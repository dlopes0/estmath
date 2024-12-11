#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "symbol_table.h"
#include "custom_math.h"

double eval(char* input, SymbolTable* symbol_table)
{
    double res = 0;

    Lexer* lexer = lexer_new(input);
    Node* ast = parse(lexer);

    res = evaluate_ast(ast, symbol_table);

    free_ast(ast);
    lexer_free(lexer);

    return res;
}

double eval_node(Node* node, SymbolTable* symbol_table)
{
    double res = 0;

    res = evaluate_ast(node, symbol_table);

    return res;
}

// 7. Calculus
// integral(a,b,f,x) - Calculate Definite Integral with Simpson's 1/3 Rule
double integral(double a, double b, Node* f, Node* x)
{
    double res = 0;

    double f_a  = 0; // f(a)
    double f_ab = 0; // f((a+b)/2)
    double f_b  = 0; // f(b)

    SymbolTable* symbol_table = symbol_table_create();

    // f(a)
    symbol_table_add(symbol_table, x->value, a, NULL);
    f_a = eval_node(f, symbol_table);

    // f((a+b)/2)
    symbol_table_add(symbol_table, x->value, ((a+b)/2), NULL);
    f_ab = eval_node(f, symbol_table);

    // f(b)
    symbol_table_add(symbol_table, x->value, b, NULL);
    f_b = eval_node(f, symbol_table);

    // Result
    res = ((b-a)/6)*(f_a+(4*f_ab)+f_b);

    symbol_table_free(symbol_table);

    return res;
}