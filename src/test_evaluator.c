#include <stdio.h>
#include <math.h>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "symbol_table.h"

void eval(char* input, SymbolTable* symbol_table)
{
    Lexer* lexer = lexer_new(input);
    Node* ast = parse(lexer);

    printf("Expression: %s\n", input);
    printf("AST:\n");
    print_ast(ast, 0);

    double result = evaluate_ast(ast, symbol_table);
    printf("Result: %f\n", result);

    free_ast(ast);
    lexer_free(lexer);
}

int main() 
{
    SymbolTable* symbol_table = symbol_table_create();

    symbol_table_add(symbol_table, "x", 5);

    char* inputs[] = {
        "2^3^2",
        "(2^3)^2",
        "3 + 4 * 2 / (1 - 5)^2^3",
        "10 - 5 * 2 + 3^2",
        "100 / (10 + 2) * 3",
        "sin(3.14/2)",
        "cos(0) + 1",
        "sin(45 * 3.14/180)",
        "sqrt(16)",
        "sqrt(4 * 9)",
        "sin(sqrt(2))",
        "-4^2",
        "(-4)^2",
        "3 + (-5 * 2)",
        "2 * 3 + 4",
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "sin(3.14/4) * sqrt(16) + 2^3",
        "cos(0) * 5 + 3 / 2",
        "sqrt(100) - 5 * 2 + 3^2",
        "pi",
        "e",
        "x",
        "2 * x",
        "sin(pi/2)",
        "cos(0)",
        "sqrt(x)"
    };
 
    int num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_inputs; i++) 
    {
        eval(inputs[i], symbol_table);
    }

    symbol_table_free(symbol_table);

    return 0;
}