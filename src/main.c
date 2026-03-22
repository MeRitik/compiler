#include "ast.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

void print_ast(AST* node);

const char* token_to_string(TokenType type) {
    switch (type) {
    case TOKEN_NUMBER:
        return "NUMBER";
    case TOKEN_PLUS:
        return "PLUS";
    case TOKEN_MINUS:
        return "MINUS";
    case TOKEN_MUL:
        return "MUL";
    case TOKEN_DIV:
        return "DIV";
    case TOKEN_LPAREN:
        return "LPAREN";
    case TOKEN_RPAREN:
        return "RPAREN";
    case TOKEN_EOF:
        return "EOF";
    default:
        return "UNKNOWN";
    }
}

int main() {
    char input[100];

    printf("Enter expression: ");
    scanf("%[^\n]", input);

    init_parser(input);

    AST* root = parse();

    // int result = interpret(root);

    printf("Parsed AST: ");
    print_ast(root);
    printf("\n");

    // printf("Result: %d\n", result);

    free_ast(root);

    return 0;
}

void print_ast(AST* node) {
    if (!node)
        return;

    if (node->type == AST_NUMBER)
        printf("%d", node->value);
    else if (node->type == AST_VARIABLE)
        printf("%s", node->name);
    else if (node->type == AST_ASSIGNMENT) {
        printf("(");
        print_ast(node->left);
        printf(" = ");
        print_ast(node->right);
        printf(")");
        return;
    } else {
        printf("(");
        print_ast(node->left);

        switch (node->type) {
        case AST_NUMBER:
            break;
        case AST_ADD:
            printf(" + ");
            break;
        case AST_SUBTRACT:
            printf(" - ");
            break;
        case AST_MULTIPLY:
            printf(" * ");
            break;
        case AST_DIVIDE:
            printf(" / ");
            break;
        }

        print_ast(node->right);
        printf(")");
    }
}