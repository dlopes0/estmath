#include <stdio.h>
#include <math.h>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "return_code.h"
#include "symbol_table.h"

void eval_test(char* input, SymbolTable* symbol_table)
{
    Lexer* lexer = lexer_new(input);
    Node* ast = parse(lexer);

    double result = evaluate_ast(ast, symbol_table);

    switch (RETURN_CODE)
    {
        case RETURN_CODE_EVAL_OK:
            printf(" %.10f\n", result);
            break;
        case RETURN_CODE_SYNTAX_ERROR:
            printf(" ? Syntax Error\n");
            break;
        case RETURN_CODE_DIV_ZERO_ERROR:
            printf(" ? Cannot divide by zero\n");
            break;
        case RETURN_CODE_MISSING_ARGS_ERROR:
            printf(" ? Missing arguments\n");
            break;
        case RETURN_CODE_UNKNOWN_FUNC_ERROR:
            printf(" ? Unknown function\n");
            break;
        case RETURN_CODE_SCI_NOTATION_ERROR:
            printf(" ? Scientific notation error\n");
            break;
        case RETURN_CODE_UNKNOWN_VARS_ERROR:
            printf(" ? Unknown function\n");
            break;
        default:
            printf(" ? Some error occurred\n");
            break;
    }

    symbol_table_add(symbol_table, "ans", result, NULL);

    free_ast(ast);
    lexer_free(lexer);
}

int main() 
{
    SymbolTable* symbol_table = symbol_table_create();

    char input[1024];
 
    while(1)
    {
        printf(">> ");
        scanf("%s", input);
        eval_test(input, symbol_table);
    }

    symbol_table_free(symbol_table);

    return 0;
}