#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

void init_parser(const char* input);
AST* parse();
AST* statement_list();

#endif