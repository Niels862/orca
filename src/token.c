#include "token.h"
#include "util.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

char const *orca_tokenkind_string(orca_tokenkind_t kind) {
    static char const *strings[] = {
        [ORCA_TOKEN_NONE]               = "(none)",
        [ORCA_TOKEN_IDENTIFIER]         = "identifier",
        [ORCA_TOKEN_INTEGER]            = "integer",
        [ORCA_TOKEN_LEFTBRACKET]        = "[",
        [ORCA_TOKEN_RIGHTBRACKET]       = "]",
        [ORCA_TOKEN_LEFTBRACE]          = "{",
        [ORCA_TOKEN_RIGHTBRACE]         = "}",
        [ORCA_TOKEN_LEFTPAREN]          = "(",
        [ORCA_TOKEN_RIGHTPAREN]         = ")",
        [ORCA_TOKEN_SEMICOLON]          = ";",
        [ORCA_TOKEN_COMMA]              = ",",
        [ORCA_TOKEN_DOT]                = ".",
        [ORCA_TOKEN_PLUS]               = "+",
        [ORCA_TOKEN_MINUS]              = "-",
        [ORCA_TOKEN_ASTERISK]           = "*",
        [ORCA_TOKEN_SLASH]              = "/",
        [ORCA_TOKEN_PERCENT]            = "%",
        [ORCA_TOKEN_LESS_THAN]          = "<",
        [ORCA_TOKEN_GREATER_THAN]       = ">",
        [ORCA_TOKEN_EQUALS]             = "=",
        [ORCA_TOKEN_EXCLAMATION_MARK]   = "!",
        [ORCA_TOKEN_PIPE]               = "|",
        [ORCA_TOKEN_AMPERSAND]          = "&",
        [ORCA_TOKEN_EOF]                = "end of file",
        [ORCA_TOKEN_STARTSOURCE]        = "start-source",
        [ORCA_TOKEN_ENDSOURCE]          = "end-source",
    };

    char const *s = strings[kind];
    assert(s != NULL);

    return s;
}

void orca_token_init(orca_token_t *token, orca_tokenkind_t kind, 
                     orca_text_position_t *pos, 
                     char const *start, char const *end) {
    token->kind = kind;
    token->pos = *pos;
    token->start = start;
    token->end = end;
}

void orca_token_write(orca_token_t *token, FILE *file) {
    if (token == NULL) {
        fprintf(file, "(null)");
        return;
    }

    orca_text_position_write(&token->pos, file);
    fprintf(file, ": <%s>: '", orca_tokenkind_string(token->kind));
    orca_string_repr(token->start, token->end, file);
    fprintf(file, "'");
}
