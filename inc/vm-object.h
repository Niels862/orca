#ifndef ORCA_VM_OBJECT_HPP
#define ORCA_VM_OBJECT_HPP

#include <inttypes.h>
#include <stdbool.h>

typedef struct orca_Type_t orca_Type_t;

typedef struct {
    orca_Type_t *type;
    bool marked;
    // ...
} orca_Object_t;

struct orca_Type_t {
    orca_Object_t object;
    orca_Type_t *super;
};

typedef struct {
    orca_Object_t object;
    char const *start;
    char const *end;
} orca_String_t;

typedef struct {
    orca_Object_t object;
    int64_t value;
} orca_Int_t;

orca_Object_t *orca_Object_new();

orca_Type_t *orca_Type_new(orca_Type_t *super);

orca_String_t *orca_String_new(char const *start, char const *end);

orca_Int_t *orca_Int_new(int64_t value);

#endif
