#include "parse-structure.h"

orca_ast_node_t *orca_parse_structure(orca_token_t *tokens) {
    orca_token_t *end = tokens;
    while (end->kind != ORCA_TOKEN_EOF) {
        end++;
    }

    orca_parser_t parser;
    orca_parser_init(&parser, tokens, end);

    if (!orca_parser_expect(&parser, ORCA_TOKEN_STARTSOURCE)) {
        return NULL;
    }

    orca_ast_node_t *stmts = orca_ast_list_new();
    while (!orca_parser_done(&parser)) {
        orca_ast_node_t *stmt = orca_parse_statement(&parser);
        if (stmt == NULL) {
            orca_ast_free(stmts);
            return NULL;
        }

        orca_ast_list_append(stmts, stmt);
    }

    return orca_ast_program_new(stmts);
}

orca_ast_node_t *orca_parse_statement(orca_parser_t *parser) {
    orca_ast_node_t *node = orca_preparse_expr(parser);

    if (orca_parser_expect(parser, ORCA_TOKEN_SEMICOLON) == NULL) {
        orca_ast_free(node);
        return NULL;
    }

    return orca_ast_expr_stmt_new(node);
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
