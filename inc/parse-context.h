#ifndef ORCA_PARSE_CONTEXT_H
#define ORCA_PARSE_CONTEXT_H

#include "parser.h"
#include "ast.h"
#include <stdbool.h>

bool orca_parse_expr_tokenrange(orca_ast_node_t **pnode);

bool orca_parse_type_tokenrange(orca_ast_node_t **pnode);

orca_ast_node_t *orca_parse_expr(orca_parser_t *parser);

orca_ast_node_t *orca_parse_value(orca_parser_t *parser);

orca_ast_node_t *orca_parse_atom(orca_parser_t *parser);

orca_ast_node_t *orca_parse_identifier(orca_parser_t *parser);

orca_ast_node_t *orca_parse_integer(orca_parser_t *parser);

orca_ast_node_t *orca_parse_bracketed(orca_parser_t *parser);

orca_ast_node_t *orca_parse_call(orca_parser_t *parser, orca_ast_node_t *func);

orca_ast_node_t *orca_parse_args(orca_parser_t *parser);

#endif
