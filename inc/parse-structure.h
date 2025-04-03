#ifndef ORCA_PARSE_STRUCTURE_H
#define ORCA_PARSE_STRUCTURE_H

#include "parser.h"
#include "ast.h"

orca_ast_node_t *orca_parse_structure(orca_token_t *tokens);

orca_ast_node_t *orca_preparse_expr(orca_parser_t *parser);

#endif
