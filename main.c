#include "lexer.h"
#include <stdio.h>

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
    
    init_lexer(input);

    Token token;
    do {
        token = get_next_token();
        printf("Token: %s, Value: %d\n", token_to_string(token.type),
               token.value);
    } while (token.type != TOKEN_EOF);

    return 0;
}