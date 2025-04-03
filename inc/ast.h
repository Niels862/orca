#ifndef ORCA_AST_H
#define ORCA_AST_H

#include "token.h"
#include "defs.h"
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

typedef enum {
    ORCA_NODE_NONE,
    
    ORCA_NODE_TOKENRANGE,

    ORCA_NODE_INTEGER,
    ORCA_NODE_IDENTIFIER,
    ORCA_NODE_CALL,
    ORCA_NODE_ARG,

    ORCA_N_NODES
} orca_nodekind_t;

typedef struct {
    orca_nodekind_t kind;
} orca_ast_base_t;

typedef struct orca_ast_node_t {
    orca_ast_base_t base;

    union {
        struct orca_ast_node_t *node;
        orca_token_t *token;
        int64_t int64;
    } attrs[];
} orca_ast_node_t;

#define ORCA_MAX_AST_ATTRS 8

typedef struct {
    char const *name;
    orca_datatype_t type;
} orca_ast_attr_t;

typedef struct {
    char const *name;
    orca_nodekind_t kind;
    orca_ast_attr_t attrs[ORCA_MAX_AST_ATTRS];
} orca_ast_descriptor_t;

typedef struct {
    orca_ast_base_t base;
    orca_token_t *start;
    orca_token_t *end;
} orca_ast_tokenrange_t;

typedef struct {
    orca_ast_base_t base;
    orca_token_t *token;
    int64_t value;
} orca_ast_integer_t;

typedef struct {
    orca_ast_base_t base;
    orca_token_t *token;
} orca_ast_identifier_t;

typedef struct {
    orca_ast_base_t base;
    orca_ast_node_t *func;
    orca_ast_node_t *args;
} orca_ast_call_t;

typedef struct {
    orca_ast_base_t base;
    orca_ast_node_t *expr;
    orca_ast_node_t *next;
} orca_ast_arg_t;

orca_ast_descriptor_t *orca_ast_descriptor(orca_nodekind_t kind);

void orca_ast_free(orca_ast_node_t *node);

void orca_ast_write(orca_ast_node_t *node, size_t depth, FILE *file);

orca_ast_node_t *orca_ast_tokenrange_new(orca_token_t *start, 
                                         orca_token_t *end);

orca_ast_node_t *orca_ast_integer_new(orca_token_t *token);

orca_ast_node_t *orca_ast_identifier_new(orca_token_t *token);

orca_ast_node_t *orca_ast_call_new(orca_ast_node_t *func, 
                                   orca_ast_node_t *args);

orca_ast_node_t *orca_ast_arg_new(orca_ast_node_t *expr);

#endif
