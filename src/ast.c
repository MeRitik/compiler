#include "ast.h"
#include <stdlib.h>
#include <string.h>

AST* create_number(int value) {
    AST* node = (AST*)malloc(sizeof(AST));
    node->type = AST_NUMBER;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AST* create_node(ASTNodeType type, AST* left, AST* right) {
    AST* node = (AST*)malloc(sizeof(AST));
    node->type = type;
    node->value = 0; // Not used for operator nodes
    node->left = left;
    node->right = right;
    return node;
}

AST* create_variable(const char* name) {
    AST* node = (AST*)malloc(sizeof(AST));
    node->type = AST_VARIABLE;
    strcpy(node->name, name);

    node->left = NULL;
    node->right = NULL;

    return node;
}

AST* create_assignment(AST* left, AST* right) {
    AST* node = (AST*)malloc(sizeof(AST));
    node->type = AST_ASSIGNMENT;

    node->left = left;
    node->right = right;

    return node;
}

AST* create_if(AST* condition, AST* body) {
    AST* node = (AST*)malloc(sizeof(AST));
    node->type = AST_IF;
    node->left = condition;
    node->right = body;

    return node;
}

void free_ast(AST* node) {
    if (node == NULL)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}