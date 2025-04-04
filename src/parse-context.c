#include "parse-context.h"
#include "util.h"

bool orca_parse_expr_tokenrange(orca_ast_node_t **pnode) {
    assert((*pnode)->base.kind == ORCA_NODE_TOKENRANGE);
    orca_ast_tokenrange_t *range = (orca_ast_tokenrange_t *)*pnode;

    orca_parser_t parser;
    orca_parser_init(&parser, range->start, range->end);

    orca_ast_node_t *node = orca_parse_expr(&parser);
    
    if (node != NULL) {
        orca_ast_free(*pnode);
        *pnode = node;
        return true;
    }

    return false;
}

bool orca_parse_type_tokenrange(orca_ast_node_t **pnode) {
    ORCA_UNUSED(pnode);
    return NULL;
}

orca_ast_node_t *orca_parse_expr(orca_parser_t *parser) {
    return orca_parse_value(parser);
}

orca_ast_node_t *orca_parse_value(orca_parser_t *parser) {
    orca_ast_node_t *value = orca_parse_atom(parser);
    if (value == NULL) {
        return NULL;
    }

    while (true) {
        switch (parser->curr->kind) {
            case ORCA_TOKEN_LEFTPAREN:
                value = orca_parse_call(parser, value);
                break;
    
            default:
                return value;
        }
    }
}

orca_ast_node_t *orca_parse_atom(orca_parser_t *parser) {
    switch (parser->curr->kind) {
        case ORCA_TOKEN_IDENTIFIER:
            return orca_parse_identifier(parser);

        case ORCA_TOKEN_INTEGER:
            return orca_parse_integer(parser);

        case ORCA_TOKEN_LEFTPAREN:
            return orca_parse_bracketed(parser);

        default:
            break;
    }

    orca_parser_expect_error(parser, "value");
    return NULL;
}

orca_ast_node_t *orca_parse_identifier(orca_parser_t *parser) {
    orca_token_t *token = orca_parser_expect(parser, ORCA_TOKEN_IDENTIFIER);
    if (token != NULL) {
        return orca_ast_identifier_new(token);
    }
    return NULL;
}

orca_ast_node_t *orca_parse_integer(orca_parser_t *parser) {
    orca_token_t *token = orca_parser_expect(parser, ORCA_TOKEN_INTEGER);
    if (token == NULL) {
        return NULL;
    }

    int64_t value = orca_string_to_int64(token->start, token->end);
    if (value < 0) {
        orca_token_error(token, "invalid integer: out of range");
        return NULL;
    }
    
    return orca_ast_integer_new(token, value);
}

orca_ast_node_t *orca_parse_bracketed(orca_parser_t *parser) {
    if (orca_parser_expect(parser, ORCA_TOKEN_LEFTPAREN) == NULL) {
        return NULL;
    }

    orca_ast_node_t *node = orca_parse_expr(parser);
    if (node == NULL) {
        return NULL;
    }

    if (orca_parser_expect(parser, ORCA_TOKEN_RIGHTPAREN) == NULL) {
        orca_ast_free(node);
        return NULL;
    }
    
    return node;
}

orca_ast_node_t *orca_parse_call(orca_parser_t *parser, orca_ast_node_t *func) {
    if (orca_parser_expect(parser, ORCA_TOKEN_LEFTPAREN) == NULL) {
        orca_ast_free(func);
        return NULL;
    }

    if (orca_parser_expect(parser, ORCA_TOKEN_RIGHTPAREN) == NULL) {
        orca_ast_free(func);
        return NULL;
    }

    return orca_ast_call_new(func, NULL);
}
