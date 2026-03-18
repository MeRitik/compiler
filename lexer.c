#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

const char* input;
char current_char;
unsigned int pos;

void advance() {
    ++pos;
    current_char = input[pos];
}

void skip_whitespace() {
    while (isspace(current_char)) {
        advance();
    }
}

int integer() {
    int result = 0;
    while (isdigit(current_char)) {
        result = result * 10 + (current_char - '0');
        advance();
    }

    return result;
}

void init_lexer(const char* input_str) {
    input = input_str;
    pos = 0;
    current_char = input[pos];
}

Token get_next_token() {
    while (current_char != '\0') {
        if (isspace(current_char)) {
            skip_whitespace();
        }

        if (isdigit(current_char)) {
            Token token;
            token.type = TOKEN_NUMBER;
            token.value = integer();
            return token;
        }

        if (current_char == '+') {
            advance();
            return (Token){TOKEN_PLUS, 0};
        }

        if (current_char == '-') {
            advance();
            return (Token){TOKEN_MINUS, 0};
        }

        if (current_char == '*') {
            advance();
            return (Token){TOKEN_MUL, 0};
        }

        if (current_char == '/') {
            advance();
            return (Token){TOKEN_DIV, 0};
        }

        if (current_char == '(') {
            advance();
            return (Token){TOKEN_LPAREN, 0};
        }

        if (current_char == ')') {
            advance();
            return (Token){TOKEN_RPAREN, 0};
        }

        printf("Error: Unknown character '%c'\n", current_char);
        exit(1);
    }

    return (Token){TOKEN_EOF, 0};
}