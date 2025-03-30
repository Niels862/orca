#ifndef ORCA_LEXER_H
#define ORCA_LEXER_H

#include "token.h"
#include "text-iterator.h"
#include <stddef.h>

typedef struct {
    orca_token_t *list;
    size_t cap;
    size_t size;
} orca_lexer_tokens_t;

typedef struct {
    orca_lexer_tokens_t tokens;
    orca_text_iterator_t base;
    orca_text_iterator_t curr;
} orca_lexer_t;

orca_token_t *orca_lex(char const *filename, char const *text);

void orca_lexer_tokens_init(orca_lexer_tokens_t *tokens);

orca_token_t *orca_lexer_tokens_append(orca_lexer_tokens_t *tokens);

orca_tokenkind_t orca_lexer_map_separator(orca_lexer_t *lexer);

void orca_lexer_init(orca_lexer_t *lexer, 
                     char const *filename, char const *text);

void orca_lexer_add(orca_lexer_t *lexer, orca_tokenkind_t kind);

#endif
