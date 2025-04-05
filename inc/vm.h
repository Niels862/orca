#ifndef ORCA_VM_H
#define ORCA_VM_H


#include "vm-gc.h"
#include "vm-bytecode.h"

typedef struct {
    orca_gc_t gc;
    orca_instr_t *instrs;
    orca_Object_t **base;
    orca_Object_t **top;
    orca_Object_t **consts;
} orca_vm_t;

void orca_vm_init(orca_vm_t *vm, orca_instr_t *instrs, orca_Object_t **consts);

void orca_vm_destruct(orca_vm_t *vm);

void orca_vm_run(orca_vm_t *vm);

#endif
