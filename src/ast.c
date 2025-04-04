#include "ast.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

orca_ast_descriptor_t tokenrange_descriptor = {
    "tokenrange", ORCA_NODE_TOKENRANGE,
    {
        { "start",      ORCA_DATATYPE_TOKEN },
        { "end",        ORCA_DATATYPE_TOKEN }
    }
};

orca_ast_descriptor_t integer_descriptor = {
    "integer", ORCA_NODE_INTEGER,
    {
        { "token",      ORCA_DATATYPE_TOKEN }, 
        { "value",      ORCA_DATATYPE_INT64 }
    }
};

orca_ast_descriptor_t identifier_descriptor = {
    "identifier", ORCA_NODE_IDENTIFIER,
    {
        { "token",      ORCA_DATATYPE_TOKEN }
    }
};

orca_ast_descriptor_t call_descriptor = {
    "call", ORCA_NODE_CALL,
    {
        { "func",       ORCA_DATATYPE_AST_NODE },
        { "args",       ORCA_DATATYPE_AST_NODE }
    }
};

orca_ast_descriptor_t arg_descriptor = {
    "arg", ORCA_NODE_ARG,
    {
        { "expr", ORCA_DATATYPE_AST_NODE },
        { "next", ORCA_DATATYPE_AST_NODE }
    }
};

orca_ast_descriptor_t *orca_ast_descriptor(orca_nodekind_t kind) {
    static orca_ast_descriptor_t *descriptors[ORCA_N_NODES] = {
        [ORCA_NODE_TOKENRANGE]      = &tokenrange_descriptor,
        [ORCA_NODE_INTEGER]         = &integer_descriptor,
        [ORCA_NODE_IDENTIFIER]      = &identifier_descriptor,
        [ORCA_NODE_CALL]            = &call_descriptor,
        [ORCA_NODE_ARG]             = &arg_descriptor
    };

    assert(kind < ORCA_N_NODES);
    orca_ast_descriptor_t *desc = descriptors[kind];
    assert(desc != NULL);

    return desc;
}

void orca_ast_free(orca_ast_node_t *node) {
    if (node == NULL) {
        return;
    }

    orca_ast_descriptor_t *desc = orca_ast_descriptor(node->base.kind);

    for (size_t i = 0; i < ORCA_MAX_AST_ATTRS; i++) {
        if (desc->attrs[i].type == ORCA_DATATYPE_AST_NODE) {
            orca_ast_free(node->attrs[i].node);
        }
    }

    free(node);
}

void orca_ast_write(orca_ast_node_t *node, size_t depth, FILE *file) {
    if (node == NULL) {
        fprintf(file, "(null)");
        return;
    }

    orca_ast_descriptor_t *desc = orca_ast_descriptor(node->base.kind);

    fprintf(file, "{\n");
    orca_write_n_chars(depth + 1, ' ', file);
    fprintf(file, "kind: %s,\n", desc->name);

    for (size_t i = 0; i < ORCA_MAX_AST_ATTRS; i++) {
        orca_ast_attr_t *attr = &desc->attrs[i];

        if (attr->type == ORCA_DATATYPE_NONE) {
            continue;
        }

        orca_write_n_chars(depth + 1, ' ', file);
        fprintf(file, "%s: ", attr->name);

        switch (attr->type) {
            case ORCA_DATATYPE_NONE:
                break;
                
            case ORCA_DATATYPE_AST_NODE:
                orca_ast_write(node->attrs[i].node, depth + 1, file);
                break;

            case ORCA_DATATYPE_TOKEN:
                orca_token_write(node->attrs[i].token, file);
                break;

            case ORCA_DATATYPE_INT64:
                fprintf(file, "%ld", node->attrs[i].int64);
                break;
        }

        fprintf(file, ",\n");
    }

    orca_write_n_chars(depth, ' ', file);
    fprintf(file, "}");
}

orca_ast_node_t *orca_ast_tokenrange_new(orca_token_t *start, 
                                         orca_token_t *end) {
    orca_ast_tokenrange_t *node = orca_xmalloc(sizeof(orca_ast_tokenrange_t));

    node->base.kind = ORCA_NODE_TOKENRANGE;
    node->start = start;
    node->end = end;

    return (orca_ast_node_t *)node;
}

orca_ast_node_t *orca_ast_integer_new(orca_token_t *token, int64_t value) {
    orca_ast_integer_t *node = orca_xmalloc(sizeof(orca_ast_integer_t));

    node->base.kind = ORCA_NODE_INTEGER;
    node->token = token;
    node->value = value;

    return (orca_ast_node_t *)node;
}

orca_ast_node_t *orca_ast_identifier_new(orca_token_t *token) {
    orca_ast_identifier_t *node = orca_xmalloc(sizeof(orca_ast_identifier_t));

    node->base.kind = ORCA_NODE_IDENTIFIER;
    node->token = token;

    return (orca_ast_node_t *)node;
}

orca_ast_node_t *orca_ast_call_new(orca_ast_node_t *func, 
                                   orca_ast_node_t *args) {
    orca_ast_call_t *node = orca_xmalloc(sizeof(orca_ast_call_t));

    node->base.kind = ORCA_NODE_CALL;
    node->func = func;
    node->args = args;

    return (orca_ast_node_t *)node;
}

orca_ast_node_t *orca_ast_arg_new(orca_ast_node_t *expr) {
    orca_ast_arg_t *node = orca_xmalloc(sizeof(orca_ast_arg_t));

    node->base.kind = ORCA_NODE_ARG;
    node->expr = expr;
    node->next = NULL;

    return (orca_ast_node_t *)node;
}
