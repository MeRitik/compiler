#include "interpreter.h"
#include "symbol_table.h"
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

    case AST_VARIABLE:
        return get_variable(node->name);

    case AST_ASSIGNMENT:
        int value = interpret(node->right);
        set_variable(node->left->name, value);
        return value;

    case AST_STATEMENT_LIST:
        interpret(node->left);
        return interpret(node->right);

    case AST_GREATER:
        return interpret(node->left) > interpret(node->right);

    case AST_LESSTHAN:
        return interpret(node->left) < interpret(node->right);

    case AST_EQUAL:
        return interpret(node->left) == interpret(node->right);

    case AST_NOT_EQUAL:
        return interpret(node->left) != interpret(node->right);

    default:
        fprintf(stderr, "Error: Unknown operator\n");
        return 0;
    }
}