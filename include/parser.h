#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

void init_parser(const char* input);
AST* parse();
void free_ast(AST* node);

#endif