#include "ast.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

void print_ast(AST* node);

int main() {

    char input[1024];

    printf("Enter program:\n");
    fgets(input, sizeof(input), stdin);

    init_parser(input);

    AST* root = parse();

    printf("Parsed AST: ");
    print_ast(root);
    printf("\n");

    int result = interpret(root);

    printf("Result: %d\n", result);

    free_ast(root);

    return 0;
}

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

void print_ast(AST* node) {
    if (!node)
        return;
    if (node->type == AST_STATEMENT_LIST) {
        print_ast(node->left);
        printf("; ");
        print_ast(node->right);
    } else if (node->type == AST_NUMBER)
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
    } else if (node->type == AST_IF) {
        printf("if(");
        print_ast(node->left);
        printf("){ ");
        print_ast(node->right);
        printf(" }");
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
        case AST_GREATER:
            printf(" > ");
            break;
        case AST_LESSTHAN:
            printf(" < ");
            break;
        case AST_EQUAL:
            printf(" == ");
            break;
        case AST_NOT_EQUAL:
            printf(" != ");
            break;
        case AST_IF:
            break;
        }

        print_ast(node->right);
        printf(")");
    }
}