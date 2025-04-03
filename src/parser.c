#include "parser.h"
#include "util.h"
#include <assert.h>

void orca_parser_init(orca_parser_t *parser, orca_token_t *tokens, 
                      orca_token_t *end) {
    assert(tokens != NULL);
    
    parser->curr = tokens;
    parser->end = end;
}

void orca_parser_forward(orca_parser_t *parser) {
    if (parser->curr != parser->end) {
        parser->curr++;
    }
}

bool orca_parser_done(orca_parser_t *parser) {
    return parser->curr == parser->end;
}

orca_token_t *orca_parser_accept(orca_parser_t *parser, orca_tokenkind_t kind) {
    orca_token_t *token = parser->curr;

    if (token->kind == kind) {
        orca_parser_forward(parser);
        return token;
    }

    return NULL;
}

orca_token_t *orca_parser_expect(orca_parser_t *parser, orca_tokenkind_t kind) {
    orca_token_t *token = parser->curr;

    if (token->kind == kind) {
        orca_parser_forward(parser);
        return token;
    }

    orca_token_error(token, "expected %s, but got %s", 
                     orca_tokenkind_string(kind), 
                     orca_tokenkind_string(token->kind));
    return NULL;
}
