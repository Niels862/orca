#include "vm.h"
#include "util.h"
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
}

void orca_vm_run(orca_vm_t *vm) {
    size_t ip = 0;

    while (1) {
        orca_instr_t instr = vm->instrs[ip];

        switch (instr.opcode) {
            case ORCA_OP_LOAD_CONST:
                fprintf(stderr, "Loading %ld\n", ((orca_Int_t *)vm->consts[instr.data])->value);
                *vm->top = vm->consts[instr.data];
                vm->top++;
                break;

            case ORCA_OP_LOAD_NULL:
                *vm->top = NULL;
                vm->top++;
                break;

            case ORCA_OP_TEMP_PRINT:
                vm->top--;
                printf("[%ld]\n", ((orca_Int_t *)(*vm->top))->value);
                break;

            case ORCA_OP_EXIT:
                return;
        }

        ip++;
    }
    ORCA_UNUSED(vm);
}
