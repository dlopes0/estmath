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
            printf(" ? Syntax Error");
            break;
        case RETURN_CODE_DIV_ZERO_ERROR:
            printf(" ? Cannot divide by zero");
            break;
        case RETURN_CODE_MISSING_ARGS_ERROR:
            printf(" ? Missing arguments");
            break;
        case RETURN_CODE_UNKNOWN_FUNC_ERROR:
            printf(" ? Unknown function");
            break;
        case RETURN_CODE_SCI_NOTATION_ERROR:
            printf(" ? Scientific notation error");
            break;
        case RETURN_CODE_UNKNOWN_VARS_ERROR:
            printf(" ? Unknown function");
            break;
        default:
            printf(" ? Some error occurred");
            break;
    }

    free_ast(ast);
    lexer_free(lexer);
}

int main() 
{
    SymbolTable* symbol_table = symbol_table_create();

    char input[1024];
 
    while(1)
    {
        scanf(">> %s\n", input);
        eval_test(input, symbol_table);
    }

    symbol_table_free(symbol_table);

    return 0;
}