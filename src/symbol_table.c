#include "symbol_table.h"
#include <string.h>

typedef struct {
    char name[64];
    int value;
} Symbol;

Symbol symbol_table[100];
int symbol_count = 0;

int get_variable(const char* name) {
    for (int i = 0; i < symbol_count; ++i) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].value;
        }
    }

    return 0; // Default value if variable not found
}

void set_variable(const char* name, int value) {
    for (int i = 0; i < symbol_count; ++i) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            symbol_table[i].value = value;
            return;
        }
    }

    // If variable not found, add it to the symbol table
    strcpy(symbol_table[symbol_count].name, name);
    symbol_table[symbol_count].value = value;
    ++symbol_count;
}