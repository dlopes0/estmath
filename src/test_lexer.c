#include <stdio.h>

#include "lexer.h"

int main() 
{
    char input[] = "func()+47";
    Lexer* lexer = lexer_new(input);
    Token* token;

    do 
    {
        token = lexer_next_token(lexer);
        printf("Token: Type=%d, Value=%s\n", token->type, token->value ? token->value : "NULL");
        token_free(token);
    }
    while (token->type != TOKEN_EOF);

    lexer_free(lexer);

    return 0;
}