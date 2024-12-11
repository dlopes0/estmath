#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "parser.h"
#include "evaluator.h"
#include "settings.h"
#include "custom_math.h"
#include "functions.h"

#define PI 3.14159265358979323846

double evaluate_function(Node* node, SymbolTable* symbol_table)
{
    // 1. Trigonometric Functions

    // sin(x) - Sine
    if (strcmp(node->value, "sin") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'sin' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        if (mode_angle == MODE_ANGLE_DEG)
        {
            return sin((evaluate_ast(node->args[0], symbol_table)*PI)/180);
        }
        else if (mode_angle == MODE_ANGLE_GRA)
        {
            return sin(evaluate_ast(node->args[0], symbol_table)*0.015708);
        }
        else
        {
            return sin(evaluate_ast(node->args[0], symbol_table));
        }
    }

    // cos(x) - Cossine
    else if (strcmp(node->value, "cos") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'cos' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        if (mode_angle == MODE_ANGLE_DEG)
        {
            return cos((evaluate_ast(node->args[0], symbol_table)*PI)/180);
        }
        else if (mode_angle == MODE_ANGLE_GRA)
        {
            return cos(evaluate_ast(node->args[0], symbol_table)*0.015708);
        }
        else
        {
            return cos(evaluate_ast(node->args[0], symbol_table));
        }
    }

    // tan(x) - Tangent
    else if (strcmp(node->value, "tan") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'tan' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        if (mode_angle == MODE_ANGLE_DEG)
        {
            return tan((evaluate_ast(node->args[0], symbol_table)*PI)/180);
        }
        else if (mode_angle == MODE_ANGLE_GRA)
        {
            return tan(evaluate_ast(node->args[0], symbol_table)*0.015708);
        }
        else
        {
            return tan(evaluate_ast(node->args[0], symbol_table));
        }
    }

    // asin(x) - Arcsine
    else if (strcmp(node->value, "asin") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'asin' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        if (mode_angle == MODE_ANGLE_DEG)
        {
            return (asin(evaluate_ast(node->args[0], symbol_table))*180)/PI;
        }
        else if (mode_angle == MODE_ANGLE_GRA)
        {
            return asin(evaluate_ast(node->args[0], symbol_table))*63.661977;
        }
        else
        {
            return asin(evaluate_ast(node->args[0], symbol_table));
        }
    }

    // acos(x) - Arccosine
    else if (strcmp(node->value, "acos") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'acos' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        if (mode_angle == MODE_ANGLE_DEG)
        {
            return (acos(evaluate_ast(node->args[0], symbol_table))*180)/PI;
        }
        else if (mode_angle == MODE_ANGLE_GRA)
        {
            return acos(evaluate_ast(node->args[0], symbol_table))*63.661977;
        }
        else
        {
            return acos(evaluate_ast(node->args[0], symbol_table));
        }
    }

    // atan(x) - Arctangent
    else if (strcmp(node->value, "atan") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'atan' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        if (mode_angle == MODE_ANGLE_DEG)
        {
            return (atan(evaluate_ast(node->args[0], symbol_table))*180)/PI;
        }
        else if (mode_angle == MODE_ANGLE_GRA)
        {
            return atan(evaluate_ast(node->args[0], symbol_table))*63.661977;
        }
        else
        {
            return atan(evaluate_ast(node->args[0], symbol_table));
        }
    }

    // sinh(x) - Hyperbolic Sine
    else if (strcmp(node->value, "sinh") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'sinh' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return sinh(evaluate_ast(node->args[0], symbol_table));
    }

    // cosh(x) - Hyperbolic Cosine
    else if (strcmp(node->value, "cosh") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'cosh' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return cosh(evaluate_ast(node->args[0], symbol_table));
    }

    // tanh(x) - Hyperbolic Tangent
    else if (strcmp(node->value, "tanh") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'tanh' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return tanh(evaluate_ast(node->args[0], symbol_table));
    }

    // asinh(x) - Hyperbolic Arcsine
    else if (strcmp(node->value, "asinh") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'asinh' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return asinh(evaluate_ast(node->args[0], symbol_table));
    }

    // acosh(x) - Hyperbolic Arccosine
    else if (strcmp(node->value, "acosh") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'acosh' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }


        return acosh(evaluate_ast(node->args[0], symbol_table));
    }

    // atanh(x) - Hyperbolic Arctangent
    else if (strcmp(node->value, "atanh") == 0)
    {
        if (node->arg_count != 1) 
        {
            fprintf(stderr, "Error: Function 'atanh' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return atanh(evaluate_ast(node->args[0], symbol_table));
    }

    // hypot(x) - Hypotenuse length, sqrt(x^2+y^2)
    else if (strcmp(node->value, "hypot") == 0)
    {
        if (node->arg_count != 2) 
        {
            fprintf(stderr, "Error: Function 'hypot' expects 2 arguments\n");
            exit(EXIT_FAILURE);
        }

        return hypot(evaluate_ast(node->args[0], symbol_table),evaluate_ast(node->args[1], symbol_table));
    }

    // 2. Exponential Functions

    // pow(x,y) - Power of y, base x
    else if (strcmp(node->value, "pow") == 0)
    {
        if (node->arg_count != 2)
        {
            fprintf(stderr, "Error: Function 'pow' expects 2 arguments\n");
            exit(EXIT_FAILURE);
        }

        return pow(evaluate_ast(node->args[0], symbol_table),evaluate_ast(node->args[1], symbol_table));
    }

    // exp(x) - e^x
    else if (strcmp(node->value, "exp") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'exp' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return exp(evaluate_ast(node->args[0], symbol_table));
    }

    // sqrt(x) - Square root of x
    else if (strcmp(node->value, "sqrt") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'sqrt' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return sqrt(evaluate_ast(node->args[0], symbol_table));
    }

    // cbrt(x) - Cube root of x
    else if (strcmp(node->value, "cbrt") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'cbrt' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return cbrt(evaluate_ast(node->args[0], symbol_table));
    }

    // 3. Logarithmic Functions
    
    // log(x) - Natural Logarithm of x
    else if (strcmp(node->value, "log") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'log' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return log(evaluate_ast(node->args[0], symbol_table));
    }

    //log10(x) - Base 10 logarithm of x
    else if (strcmp(node->value, "log10") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'log10' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return log10(evaluate_ast(node->args[0], symbol_table));
    }

    //log2(x) - Base 2 logarithm of x
    else if (strcmp(node->value, "log2") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'log2' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return log2(evaluate_ast(node->args[0], symbol_table));
    }

    // 4. Rectangular-Polar Conversion

    // atan2(x,y) - Angle theta from conversion of rectangular coordinates (x,y) to polar coordinates (r, theta)
    else if (strcmp(node->value, "atan2") == 0)
    {
        if (node->arg_count != 2)
        {
            fprintf(stderr, "Error: Function 'atan2' expects 2 argument\n");
            exit(EXIT_FAILURE);
        }

        return atan2(evaluate_ast(node->args[1], symbol_table),evaluate_ast(node->args[0], symbol_table));
    }

    // 5. Factorial, Permutation (nPr) and Combination (nCr)

    // to be continued

    // 6. Misc

    // abs(x) - Absolute value
    else if (strcmp(node->value, "abs") == 0)
    {
        if (node->arg_count != 1)
        {
            fprintf(stderr, "Error: Function 'abs' expects 1 argument\n");
            exit(EXIT_FAILURE);
        }

        return abs(evaluate_ast(node->args[0], symbol_table));
    }

    // 7. Calculus

    // integral(a,b,f,x) - Calculate Definite Integral with Simpson's 1/3 Rule
    else if (strcmp(node->value, "integral") == 0)
    {
        if (node->arg_count != 4)
        {
            fprintf(stderr, "Error: Function 'integral' expects 4 arguments\n");
            exit(EXIT_FAILURE);
        }
        
        return integral(evaluate_ast(node->args[0], symbol_table),evaluate_ast(node->args[1], symbol_table),node->args[2],node->args[3]);
    }

    else
    {
        fprintf(stderr, "Error: Unknown function '%s'\n", node->value);
        exit(EXIT_FAILURE);
    }
}