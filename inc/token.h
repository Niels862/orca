#ifndef ORCA_TOKEN_H
#define ORCA_TOKEN_H

#include "text-position.h"
#include <stdio.h>

typedef enum {
    ORCA_TOKEN_NONE,

    ORCA_TOKEN_IDENTIFIER,
    ORCA_TOKEN_INTEGER,

    ORCA_TOKEN_LEFTBRACKET,
    ORCA_TOKEN_RIGHTBRACKET,

    ORCA_TOKEN_LEFTBRACE,
    ORCA_TOKEN_RIGHTBRACE,
    
    ORCA_TOKEN_LEFTPAREN,
    ORCA_TOKEN_RIGHTPAREN,
    
    ORCA_TOKEN_SEMICOLON,
    ORCA_TOKEN_COMMA,
    ORCA_TOKEN_DOT,

    ORCA_TOKEN_PLUS,
    ORCA_TOKEN_MINUS,
    ORCA_TOKEN_ASTERISK,
    ORCA_TOKEN_SLASH,
    ORCA_TOKEN_PERCENT,

    ORCA_TOKEN_LESS_THAN,
    ORCA_TOKEN_GREATER_THAN,
    ORCA_TOKEN_EQUALS,
    ORCA_TOKEN_EXCLAMATION_MARK,

    ORCA_TOKEN_PIPE,
    ORCA_TOKEN_AMPERSAND,

    ORCA_TOKEN_ARROW,

    ORCA_TOKEN_EOF,
    ORCA_TOKEN_STARTSOURCE,
    ORCA_TOKEN_ENDSOURCE,

    ORCA_TOKENS_N
} orca_tokenkind_t;

typedef struct {
    orca_tokenkind_t kind;
    orca_text_position_t pos;
    char const *start;
    char const *end;
} orca_token_t;

char const *orca_tokenkind_string(orca_tokenkind_t kind);

void orca_token_init(orca_token_t *token, orca_tokenkind_t kind, 
                     orca_text_position_t *pos, 
                     char const *start, char const *end);

void orca_token_write(orca_token_t *token, FILE *file);

#endif
