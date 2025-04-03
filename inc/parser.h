#ifndef ORCA_PARSER_H
#define ORCA_PARSER_H

#include "token.h"
#include <stdbool.h>

typedef struct {
    orca_token_t *curr;
    orca_token_t *end;
} orca_parser_t;

void orca_parser_init(orca_parser_t *parser, orca_token_t *tokens, 
                      orca_token_t *end);

void orca_parser_forward(orca_parser_t *parser);

bool orca_parser_done(orca_parser_t *parser);

orca_token_t *orca_parser_accept(orca_parser_t *parser, orca_tokenkind_t kind);

orca_token_t *orca_parser_expect(orca_parser_t *parser, orca_tokenkind_t kind);

#endif
