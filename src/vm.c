#include "vm.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void orca_vm_init(orca_vm_t *vm, orca_instr_t *instrs, orca_Object_t **consts) {
    orca_gc_init(&vm->gc);
    vm->instrs = instrs;
    vm->base = orca_xmalloc(4096 * sizeof(orca_Object_t *));
    vm->top = vm->base;
    vm->consts = consts;
}

void orca_vm_destruct(orca_vm_t *vm) {
    orca_gc_destruct(&vm->gc);
    free(vm->base);
}

orca_Object_t *orca_vm_run(orca_vm_t *vm) {
    size_t ip = 0;

    while (1) {
        orca_instr_t instr = vm->instrs[ip];

        switch (instr.opcode) {
            case ORCA_OP_LOAD_CONST:
                fprintf(stderr, "Loading %ld\n", ((orca_Int_t *)vm->consts[instr.data])->value);
                ORCA_PUSH(vm, vm->consts[instr.data]);
                break;

            case ORCA_OP_LOAD_NULL:
                ORCA_PUSH(vm, NULL);
                break;

            case ORCA_OP_TEMP_PRINT:
                printf("[%ld]\n", ((orca_Int_t *)ORCA_POP(vm))->value);
                break;

            case ORCA_OP_EXIT:
                longjmp(vm->state, ORCA_UNWIND_EXIT);
        }

        ip++;
    }

    return NULL;
}
