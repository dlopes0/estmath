#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"

typedef enum {
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_FUNCTION,
    NODE_OPERATOR
} NodeType;

typedef struct Node {
    NodeType type;
    char* value;
    struct Node* left;
    struct Node* right;
    struct Node** args;
    int arg_count;
} Node;

Node* node_new(NodeType type, char* value);
Node* parse_primary(Lexer* lexer);
Node* parse_binary(Lexer* lexer, int precedence);
Node* parse_expression(Lexer* lexer);
Node* parse(Lexer* lexer);
const char* get_node_type(NodeType type);
void print_ast(Node* node, int indent);
void free_ast(Node* node);

#endif