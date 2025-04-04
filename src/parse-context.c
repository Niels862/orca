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
    return orca_parse_integer(parser);
}

orca_ast_node_t *orca_parse_integer(orca_parser_t *parser) {
    orca_token_t *token = orca_parser_expect(parser, ORCA_TOKEN_INTEGER);
    if (token != NULL) {
        int64_t value = orca_string_to_int64(token->start, token->end);
        if (value < 0) {
            orca_token_error(token, "invalid integer: out of range");
            return NULL;
        }
        return orca_ast_integer_new(token, value);
    }
    return NULL;
}
