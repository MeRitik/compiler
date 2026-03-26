#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,

    TOKEN_GREATER,
    TOKEN_LESSTHAN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_EOF,

    TOKEN_SEMICOLON
} TokenType;

typedef struct {
    TokenType type;
    int value;
    char name[64];
} Token;

void init_lexer(const char* input);
Token get_next_token();
Token peek_next_token();

#endif