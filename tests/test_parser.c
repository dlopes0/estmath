#include <stdio.h>

#include "lexer.h"
#include "parser.h"
#include "settings.h"

int main() 
{
    mode_debug = 1;

    char* input = "INT(0,1,x^2,x)";

    Lexer* lexer = lexer_new(input);
    Node* ast = parse(lexer);

    // Print the AST
    printf("AST:\n");
    print_ast(ast, 0);

    // Free allocated memory
    free_ast(ast);
    lexer_free(lexer);

    return 0;
}