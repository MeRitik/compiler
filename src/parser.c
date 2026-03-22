#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

Token current_token;

static void eat(TokenType type);
static AST* factor();
static AST* term();
static AST* expr();

static void eat(TokenType type) {
    if (current_token.type == type) {
        current_token = get_next_token();
    } else {
        fprintf(stderr, "Syntax error: expected token type %d, got %d\n", type,
                current_token.type);
        exit(EXIT_FAILURE);
    }
}

static AST* factor() {
    Token token = current_token;

    if (token.type == TOKEN_NUMBER) {
        eat(TOKEN_NUMBER);
        return create_number(token.value);
    } else if (token.type == TOKEN_LPAREN) {
        eat(TOKEN_LPAREN);
        AST* node = expr();
        eat(TOKEN_RPAREN);
        return node;
    } else {
        fprintf(stderr,
                "Syntax error: expected number or '(', got token type %d\n",
                token.type);
        exit(EXIT_FAILURE);
    }
}

static AST* term() {
    AST* node = factor();

    while (current_token.type == TOKEN_MUL || current_token.type == TOKEN_DIV) {
        Token token = current_token;

        if (token.type == TOKEN_MUL) {
            eat(TOKEN_MUL);
            node = create_node(AST_MULTIPLY, node, factor());
        } else if (token.type == TOKEN_DIV) {
            eat(TOKEN_DIV);
            node = create_node(AST_DIVIDE, node, factor());
        }
    }

    return node;
}

static AST* expr() {
    AST* node = term();

    while (current_token.type == TOKEN_PLUS ||
           current_token.type == TOKEN_MINUS) {
        Token token = current_token;

        if (token.type == TOKEN_PLUS) {
            eat(TOKEN_PLUS);
            node = create_node(AST_ADD, node, term());
        } else {
            eat(TOKEN_MINUS);
            node = create_node(AST_SUBTRACT, node, term());
        }
    }

    return node;
}

AST* statement() {
    if (current_token.type == TOKEN_IDENTIFIER) {
        Token token = current_token;
        eat(TOKEN_IDENTIFIER);

        if (current_token.type == TOKEN_ASSIGN) {
            eat(TOKEN_ASSIGN);
            AST* right = expr();
            AST* left = create_variable(token.name);
            return create_assignment(left, right);
        }
    }

    return expr();
}

AST* parse() {
    current_token = get_next_token();
    return statement();
}

void init_parser(const char* text) { init_lexer(text); }