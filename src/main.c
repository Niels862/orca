#include "lexer.h"
#include "parse-structure.h"
#include "parse-context.h"
#include "util.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

#include "vm.h"

int test_parse(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s [filename]\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    char *text = orca_read_file(filename);
    if (text == NULL) {
        fprintf(stderr, "could not open file: %s\n", filename);
        return 1;
    }

    orca_token_t *tokens = orca_lex(filename, text);
    if (tokens == NULL) {
        free(text);
        return 1;
    }

    orca_token_t *curr = tokens;
    while (1) {
        orca_token_write(curr, stderr);
        fprintf(stderr, "\n");

        if (curr->kind == ORCA_TOKEN_ENDSOURCE) {
            break;
        }
        curr++;
    }

    orca_ast_node_t *node = orca_parse_structure(tokens);

    if (node != NULL) {
        orca_ast_write(node, 0, stderr);
        fprintf(stderr, "\n");

        if (orca_parse_expr_tokenrange(&node)) {
            orca_ast_write(node, 0, stderr);
            fprintf(stderr, "\n");
        }

        orca_ast_free(node);
    }

    free(text);
    free(tokens);

    return 0;
}

void test_vm() {
    orca_object_tracker_t consts;
    orca_object_tracker_init(&consts);

    orca_object_tracker_add(&consts, &orca_Int_new(0)->object);
    orca_object_tracker_add(&consts, &orca_Int_new(42)->object);

    orca_instr_t instrs[] = {
        { ORCA_OP_LOAD_NULL,    0 },
        { ORCA_OP_LOAD_CONST,   1 },
        { ORCA_OP_TEMP_PRINT,   0 },
        { ORCA_OP_LOAD_CONST,   0 },
        { ORCA_OP_EXIT,         0 }
    };

    orca_vm_t vm;
    orca_vm_init(&vm, instrs, consts.objs);

    switch (setjmp(vm.state)) {
        case ORCA_UNWIND_SETUP:
            orca_vm_run(&vm);
            break;

        case ORCA_UNWIND_EXIT:
            fprintf(stderr, "Exited with %ld\n", 
                    ((orca_Int_t *)ORCA_POP(&vm))->value);
            break;

        default:
            assert(1);
    }

    orca_vm_destruct(&vm);
    orca_object_tracker_destruct(&consts);
}

int main(int argc, char *argv[]) {
    ORCA_UNUSED(argc), ORCA_UNUSED(argv);

    test_vm();

    return 0;
}
