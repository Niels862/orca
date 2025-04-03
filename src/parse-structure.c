#include "parse-structure.h"

orca_ast_node_t *orca_parse_structure(orca_token_t *tokens) {
    orca_token_t *end = tokens;
    while (end->kind != ORCA_TOKEN_ENDSOURCE) {
        end++;
    }

    orca_parser_t parser;
    orca_parser_init(&parser, tokens, end);

    if (!orca_parser_expect(&parser, ORCA_TOKEN_STARTSOURCE)) {
        return NULL;
    }

    return orca_preparse_expr(&parser);
}

orca_ast_node_t *orca_preparse_expr(orca_parser_t *parser) {
    orca_token_t *start = parser->curr;

    while (!orca_parser_done(parser)) {
        switch (parser->curr->kind) {
            case ORCA_TOKEN_IDENTIFIER:
            case ORCA_TOKEN_INTEGER:
            case ORCA_TOKEN_LEFTBRACKET:
            case ORCA_TOKEN_RIGHTBRACKET:
            case ORCA_TOKEN_LEFTBRACE:
            case ORCA_TOKEN_RIGHTBRACE:
            case ORCA_TOKEN_LEFTPAREN:
            case ORCA_TOKEN_RIGHTPAREN:
            case ORCA_TOKEN_SEMICOLON:
            case ORCA_TOKEN_COMMA:
            case ORCA_TOKEN_DOT:
            case ORCA_TOKEN_PLUS:
            case ORCA_TOKEN_MINUS:
            case ORCA_TOKEN_ASTERISK:
            case ORCA_TOKEN_SLASH:
            case ORCA_TOKEN_PERCENT:
            case ORCA_TOKEN_LESS_THAN:
            case ORCA_TOKEN_GREATER_THAN:
            case ORCA_TOKEN_EQUALS:
            case ORCA_TOKEN_EXCLAMATION_MARK:
            case ORCA_TOKEN_PIPE:
            case ORCA_TOKEN_AMPERSAND:
            case ORCA_TOKEN_ARROW:
                break;

            default:
                goto end;
        
        }

        orca_parser_forward(parser);
    }

end:
    return orca_ast_tokenrange_new(start, parser->curr);
}
