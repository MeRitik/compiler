#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,
    AST_VARIABLE,
    AST_ASSIGN
} ASTNodeType;

typedef struct AST {
    ASTNodeType type;
    int value;
    char name[64];

    struct AST* left;
    struct AST* right;
} AST;

AST* create_number(int value);
AST* create_node(ASTNodeType type, AST* left, AST* right);
AST* create_variable(const char* name);
AST* create_assignment(const char* name, AST* value);
void free_ast(AST* node);

#endif