#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_VARIABLE,

    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,

    AST_GREATER,
    AST_LESSTHAN,
    AST_EQUAL,
    AST_NOT_EQUAL,

    AST_ASSIGNMENT,
    AST_STATEMENT_LIST,

    AST_IF
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
AST* create_assignment(AST* left, AST* value);
AST* create_if(AST* condition, AST* body);

void free_ast(AST* node);

#endif