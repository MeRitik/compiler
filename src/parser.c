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
static AST* comparison();

AST* comparison() {

    AST* node = expr();

    while (current_token.type == TOKEN_GREATER ||
           current_token.type == TOKEN_LESSTHAN ||
           current_token.type == TOKEN_EQUAL ||
           current_token.type == TOKEN_NOT_EQUAL) {

        Token token = current_token;

        if (token.type == TOKEN_GREATER) {
            eat(TOKEN_GREATER);
            node = create_node(AST_GREATER, node, expr());
        } else if (token.type == TOKEN_LESSTHAN) {
            eat(TOKEN_LESSTHAN);
            node = create_node(AST_LESSTHAN, node, expr());
        } else if (token.type == TOKEN_EQUAL) {
            eat(TOKEN_EQUAL);
            node = create_node(AST_EQUAL, node, expr());
        } else if (token.type == TOKEN_NOT_EQUAL) {
            eat(TOKEN_NOT_EQUAL);
            node = create_node(AST_NOT_EQUAL, node, expr());
        }
    }

    return node;
}

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
    } else if (token.type == TOKEN_IDENTIFIER) {
        eat(TOKEN_IDENTIFIER);
        return create_variable(token.name);
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

        Token id_token = current_token;

        // Look ahead
        Token next = peek_next_token();

        if (next.type == TOKEN_ASSIGN) {

            eat(TOKEN_IDENTIFIER);
            eat(TOKEN_ASSIGN);

            AST* right = comparison();
            AST* left = create_variable(id_token.name);

            return create_assignment(left, right);
        }
    }

    return comparison();
}

AST* statement_list() {
    AST* node = statement();

    while (current_token.type == TOKEN_SEMICOLON) {
        eat(TOKEN_SEMICOLON);
        if (current_token.type == TOKEN_EOF) {
            break;
        }
        node = create_node(AST_STATEMENT_LIST, node, statement());
    }

    return node;
}

AST* parse() {
    current_token = get_next_token();
    return statement_list();
}

void init_parser(const char* text) { init_lexer(text); }