#include <stdlib.h>
#include "ast.h"

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