#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "lexer.h"

char *strndup(const char *s, size_t n) 
{
    char *p;
    size_t n1;

    for (n1 = 0; n1 < n && s[n1] != '\0'; n1++)
        continue;
    p = malloc(n + 1);
    if (p != NULL) {
        memcpy(p, s, n1);
        p[n1] = '\0';
    }
    return p;
}

// Create new lexer
Lexer* lexer_new(char* input)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->pos = 0;
    return lexer;
}

// Get the next token from the lexer
Token* lexer_next_token(Lexer* lexer)
{
    // Skip space character
    while (lexer->pos < strlen(lexer->input) && isspace(lexer->input[lexer->pos]))
    {
        lexer->pos++;
    }

    // Check for EOF character
    if (lexer->pos >= strlen(lexer->input))
    {
        Token* token = malloc(sizeof(Token));
        token->type = TOKEN_EOF;
        token->value = NULL;

        return token;
    }

    // Check for numbers
    if (isdigit(lexer->input[lexer->pos]))
    {
        int start = lexer->pos;

        while (lexer->pos < strlen(lexer->input) && isdigit(lexer->input[lexer->pos]))
        {
            lexer->pos++;
        }

        if (lexer->pos < strlen(lexer->input) && lexer->input[lexer->pos] == '.')
        {
            lexer->pos++;

            while (lexer->pos < strlen(lexer->input) && isdigit(lexer->input[lexer->pos]))
            {
                lexer->pos++;
            }
        }

        Token* token = malloc(sizeof(Token));
        token->type = TOKEN_NUMBER;
        token->value = strndup(lexer->input + start, lexer->pos - start);
        return token;
    }

    // Check for functions and variables
    if (isalpha(lexer->input[lexer->pos]) || lexer->input[lexer->pos] == '_')
    {
        int start = lexer->pos;

        while (lexer->pos < strlen(lexer->input) && (isalnum(lexer->input[lexer->pos]) || lexer->input[lexer->pos] == '_')) 
        {
            lexer->pos++;
        }

        if (lexer->pos < strlen(lexer->input) && lexer->input[lexer->pos] == '(')
        {
            Token* token = malloc(sizeof(Token));
            token->type = TOKEN_FUNCTION;
            token->value = strndup(lexer->input + start, lexer->pos - start);
            
            return token;
        }

        Token* token = malloc(sizeof(Token));
        token->type = TOKEN_VARIABLE;
        token->value = strndup(lexer->input + start, lexer->pos - start);
        
        return token;
    }

    // Check for operators
    if (strchr("+-*/^", lexer->input[lexer->pos])) 
    {
        Token* token = malloc(sizeof(Token));
        token->type = TOKEN_OPERATOR;
        token->value = strndup(&lexer->input[lexer->pos], 1);
        lexer->pos++;
        return token;
    }

    // Check for single-character tokens
    if (strchr("(),", lexer->input[lexer->pos])) 
    {
        TokenType type = (lexer->input[lexer->pos] == '(') ? TOKEN_LPAREN :
                         (lexer->input[lexer->pos] == ')') ? TOKEN_RPAREN : TOKEN_COMMA;
        Token* token = malloc(sizeof(Token));
        token->type = type;
        token->value = strndup(&lexer->input[lexer->pos], 1);
        lexer->pos++;
        
        return token;
    }

    // Unknown character
    fprintf(stderr, "Error: Unknown character '%c'\n", lexer->input[lexer->pos]);
    exit(EXIT_FAILURE);
}

// Free the token
void token_free(Token* token) 
{
    if (token->value) 
    {
        free(token->value);
    }
    free(token);
}

// Free the lexer
void lexer_free(Lexer* lexer) 
{
    free(lexer);
}