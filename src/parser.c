#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "lexer.h"
#include "settings.h"
#include "return_code.h"
#include "parser.h"

char* strdup(const char* s)
{
    size_t size = strlen(s) + 1;

    char* p = malloc(size);

    if (p != NULL) 
    {
        memcpy(p, s, size);
    }

    return p;
}

// Create a new node
Node* node_new(NodeType type, char* value)
{
    Node* node = malloc(sizeof(Node));
    
    node->type = type;
    node->value = strdup(value);
    node->left = NULL;
    node->right = NULL;
    node->args = NULL;
    node->arg_count = 0;

    return node;
}

// Get operator precedence
int get_operator_precedence(const char* op)
{
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 2;
    if (strcmp(op, "^") == 0) return 3;
    return 0;  // Lowest precedence
}

// Parse primary expressions (numbers, variables, functions, parentheses)
Node* parse_primary(Lexer* lexer)
{
    Token* token = lexer_next_token(lexer);
    Node* node = NULL;

    switch (token->type)
    {
        case TOKEN_NUMBER:
            node = node_new(NODE_NUMBER, token->value);
            break;
        case TOKEN_OPERATOR:
            if (strcmp(token->value, "-") == 0)
            {
                Node* right = parse_primary(lexer);
                node = node_new(NODE_OPERATOR, "-");
                node->left = NULL;
                node->right = right;
            }
            break;
        case TOKEN_VARIABLE:
            node = node_new(NODE_VARIABLE, token->value);
            break;
        case TOKEN_FUNCTION:
            node = node_new(NODE_FUNCTION, token->value);

            // Expect '(' after the function name
            Token* lparen = lexer_next_token(lexer);
            if (lparen->type != TOKEN_LPAREN) 
            {
                if (mode_debug)
                {
                    fprintf(stderr, "Error: Expected '(' after function name\n");
                    exit(EXIT_FAILURE);
                }

                return_code_set(RETURN_CODE_SYNTAX_ERROR);

                break;
            }
            token_free(lparen);

            // Parse function arguments
            node->args = malloc(sizeof(Node*) * 10);  // Assume max 10 arguments for simplicity
            node->arg_count = 0;

            while (1)
            {
                node->args[node->arg_count++] = parse_expression(lexer);

                Token* next = lexer_next_token(lexer);
                if (next->type == TOKEN_RPAREN) 
                {
                    token_free(next);

                    break;  // End of arguments
                } 
                else if (next->type == TOKEN_COMMA) 
                {
                    token_free(next);  // Continue to next argument
                } 
                else 
                {
                    if (mode_debug)
                    {
                        fprintf(stderr, "Error: Expected ',' or ')'\n");
                        exit(EXIT_FAILURE);
                    }

                    return_code_set(RETURN_CODE_SYNTAX_ERROR);

                    break;
                }
            }

            break;
        case TOKEN_LPAREN: 
            node = parse_expression(lexer);  // Parse inside the parentheses

            Token* rparen = lexer_next_token(lexer);

            if (rparen->type != TOKEN_RPAREN)
            {
                if (mode_debug)
                {
                    fprintf(stderr, "Error: Expected closing parenthesis\n");
                    exit(EXIT_FAILURE);
                }

                return_code_set(RETURN_CODE_SYNTAX_ERROR);

                break;
            }

            token_free(rparen);

            break;
        default:
            if (mode_debug)
            {
                fprintf(stderr, "Error: Unexpected token in parse_primary\n");
                exit(EXIT_FAILURE);
            }

            return_code_set(RETURN_CODE_SYNTAX_ERROR);

            break;
            
    }

    token_free(token);

    return node;
}

// Parse binary expressions based on precedence
Node* parse_binary(Lexer* lexer, int precedence) 
{
    Node* left = parse_primary(lexer);

    while (1)
    {
        Token* token = lexer_next_token(lexer);
        if (token->type != TOKEN_OPERATOR) 
        {
            lexer->pos--;  // Unconsume the token
            token_free(token);
            break;
        }

        int token_precedence = get_operator_precedence(token->value);

        if (token_precedence < precedence) 
        {
            lexer->pos--;  // Unconsume the token
            token_free(token);
            break;
        }

        Node* operator = node_new(NODE_OPERATOR, token->value);

        if (strcmp(token->value, "=") == 0) 
        {
            operator->left = left;
            operator->right = parse_expression(lexer); // Assignment binds tightly
            token_free(token);

            return operator;
        }

        Node* right;

        if (strcmp(token->value, "^") == 0) 
        {
            right = parse_binary(lexer, token_precedence); // Right side with same precedence
        } 
        else 
        {
            right = parse_binary(lexer, token_precedence + 1); // Increment for other operators
        }

        operator->left = left;
        operator->right = right;

        left = operator;  // Build the tree upwards

        token_free(token);
    }

    return left;
}

// Parse an expression
Node* parse_expression(Lexer* lexer) 
{
    return parse_binary(lexer, 0);
}

// Parse input
Node* parse(Lexer* lexer) 
{
    return parse_expression(lexer);
}

// Convert NodeType to string for printing
const char* get_node_type(NodeType type)
{
    switch (type)
    {
        case NODE_NUMBER: return "NUMBER";
        case NODE_VARIABLE: return "VARIABLE";
        case NODE_FUNCTION: return "FUNCTION";
        case NODE_OPERATOR: return "OPERATOR";
        default: return "UNKNOWN";
    }
}

// Print the AST
void print_ast(Node* node, int indent)
{
    if (node == NULL) return;

    for (int i = 0; i < indent; i++)
    {
        printf("  ");
    }
    printf("%s: %s\n", get_node_type(node->type), node->value ? node->value : "NULL");

    if (node->type == NODE_FUNCTION && node->arg_count > 0) 
    {
        for (int i = 0; i < node->arg_count; i++)
        {
            print_ast(node->args[i], indent + 1);
        }
    }
    else
    {
        if (node->left) print_ast(node->left, indent + 1);
        if (node->right) print_ast(node->right, indent + 1);
    }
}

// Free the AST nodes
void free_ast(Node* node)
{
    if (node == NULL) return;

    if (node->type == NODE_FUNCTION && node->args != NULL)
    {
        for (int i = 0; i < node->arg_count; i++)
        {
            free_ast(node->args[i]);
        }
        free(node->args);
    }

    free_ast(node->left);
    free_ast(node->right);
    free(node->value);
    free(node);
}