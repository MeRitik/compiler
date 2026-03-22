#include "interpreter.h"
#include <stdio.h>

int interpret(const AST* node) {
    if (node->type == AST_NUMBER) {
        return node->value;
    }

    int left = interpret(node->left);
    int right = interpret(node->right);

    switch (node->type) {
    case AST_ADD:
        return left + right;

    case AST_SUBTRACT:
        return left - right;

    case AST_MULTIPLY:
        return left * right;

    case AST_DIVIDE:
        if (right == 0) {
            fprintf(stderr, "Error: Division by zero\n");
            return 0;
        }

        return left / right;

    default:
        fprintf(stderr, "Error: Unknown operator\n");
        return 0;
    }
}