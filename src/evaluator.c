#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "parser.h"
#include "evaluator.h"

// Evaluate the AST
double evaluate_ast(Node* node, SymbolTable* symbol_table)
{
    if (node == NULL) 
    {
        fprintf(stderr, "Error: NULL node in evaluate_ast\n");
        exit(EXIT_FAILURE);
    }

    switch (node->type)
    {
        case NODE_NUMBER:
            return atof(node->value);

        case NODE_VARIABLE:
            return symbol_table_get(symbol_table, node->value);

        case NODE_FUNCTION:
            if (strcmp(node->value, "sin") == 0)
            {
                if (node->arg_count != 1) {
                    fprintf(stderr, "Error: Function 'sin' expects 1 argument\n");
                    exit(EXIT_FAILURE);
                }

                return sin(evaluate_ast(node->args[0], symbol_table));
            }

            else if (strcmp(node->value, "cos") == 0)
            {
                if (node->arg_count != 1) {
                    fprintf(stderr, "Error: Function 'cos' expects 1 argument\n");
                    exit(EXIT_FAILURE);
                }

                return cos(evaluate_ast(node->args[0], symbol_table));
            }

            else if (strcmp(node->value, "sqrt") == 0)
            {
                if (node->arg_count != 1)
                {
                    fprintf(stderr, "Error: Function 'sqrt' expects 1 argument\n");
                    exit(EXIT_FAILURE);
                }

                return sqrt(evaluate_ast(node->args[0], symbol_table));
            }

            else
            {
                fprintf(stderr, "Error: Unknown function '%s'\n", node->value);
                exit(EXIT_FAILURE);
            }

        case NODE_OPERATOR:
            if (strcmp(node->value, "+") == 0)
            {
                return evaluate_ast(node->left, symbol_table) + evaluate_ast(node->right, symbol_table);
            }
            else if (strcmp(node->value, "-") == 0 && node->right != NULL && node->left == NULL)
            {
                return -evaluate_ast(node->right, symbol_table);
            }
            else if (strcmp(node->value, "-") == 0 && node->right != NULL)
            {
                return evaluate_ast(node->left, symbol_table) - evaluate_ast(node->right, symbol_table);
            }
            else if (strcmp(node->value, "*") == 0)
            {
                return evaluate_ast(node->left, symbol_table) * evaluate_ast(node->right, symbol_table);
            }
            else if (strcmp(node->value, "/") == 0)
            {
                double denominator = evaluate_ast(node->right, symbol_table);

                if (denominator == 0)
                {
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }

                return evaluate_ast(node->left, symbol_table) / denominator;
            } 
            else if (strcmp(node->value, "^") == 0)
            {
                return pow(evaluate_ast(node->left, symbol_table), evaluate_ast(node->right, symbol_table));
            }
            else 
            {
                fprintf(stderr, "Error: Unknown operator '%s'\n", node->value);
                exit(EXIT_FAILURE);
            }

        default:
            fprintf(stderr, "Error: Unknown node type in evaluate_ast\n");
            exit(EXIT_FAILURE);
    }
}