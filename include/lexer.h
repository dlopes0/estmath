#pragma once

#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// Lexer state
typedef struct {
    char* input;
    int pos;
} Lexer;

Lexer* lexer_new(char* input);
Token* lexer_next_token(Lexer* lexer);
void token_free(Token* token);
void lexer_free(Lexer* lexer);

#endif