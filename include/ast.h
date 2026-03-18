#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE
} ASTNodeType;

typedef struct AST {
    ASTNodeType type;
    int value;
    struct AST* left;
    struct AST* right;
} AST;

AST* create_number(int value);
AST* create_node(ASTNodeType type, AST* left, AST* right);

#endif