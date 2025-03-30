#include "lexer.h"
#include "classify.h"
#include "util.h"
#include "ctype.h"
#include <stdlib.h>

orca_token_t *orca_lex(char const *filename, char const *text) {
    orca_lexer_t lexer;
    orca_lexer_init(&lexer, filename, text);

    orca_lexer_add(&lexer, ORCA_TOKEN_STARTSOURCE);

    while (!orca_text_iterator_at_end(&lexer.curr)) {
        lexer.base = lexer.curr;
        char c = orca_text_iterator_get(&lexer.curr);

        if (orca_is_identifier_start(c)) {
            do {
                c = orca_text_iterator_next(&lexer.curr);
            } while (orca_is_identifier_continue(c));

            orca_lexer_add(&lexer, ORCA_TOKEN_IDENTIFIER);
        } else if (orca_is_integer_start(c)) {
            do {
                c = orca_text_iterator_next(&lexer.curr);
            } while (orca_is_integer_continue(c));

            orca_lexer_add(&lexer, ORCA_TOKEN_INTEGER);
        } else if (orca_is_special(c)) {
            orca_tokenkind_t kind = orca_map_special(c);
            orca_text_iterator_next(&lexer.curr);

            orca_lexer_add(&lexer, kind);
        } else if (orca_is_comment_start(c)) {
            do {
                c = orca_text_iterator_next(&lexer.curr);
            } while (!orca_text_iterator_at_end(&lexer.curr)
                     && !orca_is_newline(c));
        } else if (orca_is_whitespace(c)) {
            do {
                c = orca_text_iterator_next(&lexer.curr);
            } while (orca_is_whitespace(c));
        } else {
            orca_text_iterator_next(&lexer.curr);
            orca_range_error(lexer.base.text, &lexer.base.pos, &lexer.curr.pos, 
                             "unrecognized character: '%c'", c);
            free(lexer.tokens.list);
            return NULL;
        }
    }

    orca_lexer_add(&lexer, ORCA_TOKEN_ENDSOURCE);

    return lexer.tokens.list;
}

void orca_lexer_tokens_init(orca_lexer_tokens_t *tokens) {
    tokens->cap = 256;
    tokens->list = orca_xmalloc(tokens->cap * sizeof(orca_token_t));
    tokens->size = 0;
}

orca_token_t *orca_lexer_tokens_append(orca_lexer_tokens_t *tokens) {
    if (tokens->size >= tokens->cap) {
        tokens->cap *= 2;
        tokens->list = orca_xrealloc(tokens->list, 
                                     tokens->cap * sizeof(orca_token_t));
    }

    orca_token_t *token = &tokens->list[tokens->size];
    tokens->size++;

    return token;
}

void orca_lexer_init(orca_lexer_t *lexer, 
                     char const *filename, char const *text) {
    orca_lexer_tokens_init(&lexer->tokens);
    orca_text_iterator_init(&lexer->curr, filename, text);
    lexer->base = lexer->curr;
}

void orca_lexer_add(orca_lexer_t *lexer, orca_tokenkind_t kind) {
    orca_token_t *token = orca_lexer_tokens_append(&lexer->tokens);
    orca_token_init(token, kind, &lexer->base.pos, 
                    lexer->base.text, lexer->curr.text);
}
