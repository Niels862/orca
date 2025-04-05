#ifndef ORCA_VM_BYTECODE_H
#define ORCA_VM_BYTECODE_H

#include <inttypes.h>

typedef enum {
    ORCA_OP_LOAD_CONST,
    ORCA_OP_LOAD_NULL,

    ORCA_OP_TEMP_PRINT, /* Placeholder for system print */

    ORCA_OP_EXIT,
} orca_opcode_t;

typedef struct {
    uint32_t opcode; /* = orca_opcode_t */
    uint32_t data;
} orca_instr_t;

#endif
