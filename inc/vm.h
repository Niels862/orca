#ifndef ORCA_VM_H
#define ORCA_VM_H


#include "vm-gc.h"
#include "vm-bytecode.h"
#include <setjmp.h>

typedef enum {
    ORCA_UNWIND_SETUP,

    ORCA_UNWIND_EXIT
} orca_unwind_state_t;

typedef struct {
    orca_gc_t gc;
    orca_instr_t *instrs;
    orca_Object_t **base;
    orca_Object_t **top;
    orca_Object_t **consts;
    jmp_buf state;
} orca_vm_t;

#define ORVA_PEEK(vm)       (*((vm)->top - 1))
#define ORCA_POP(vm)        ((vm)->top--, *(vm)->top)
#define ORCA_PUSH(vm, o)    (*(vm)->top = (o), (vm)->top++)   

void orca_vm_init(orca_vm_t *vm, orca_instr_t *instrs, orca_Object_t **consts);

void orca_vm_destruct(orca_vm_t *vm);

orca_Object_t *orca_vm_run(orca_vm_t *vm);

#endif
