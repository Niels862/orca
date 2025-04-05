#include "vm-object.h"
#include "util.h"

orca_Object_t *orca_Object_new() {
    orca_Object_t *obj = orca_xmalloc(sizeof(orca_Object_t));

    obj->type = NULL;

    return obj;
}

orca_Type_t *orca_Type_new(orca_Type_t *super) {
    orca_Type_t *type = orca_xmalloc(sizeof(orca_Type_t));

    type->super = super;

    return type;
}

orca_String_t *orca_String_new(char const *start, char const *end) {
    orca_String_t *str = orca_xmalloc(sizeof(orca_String_t));

    str->start = start;
    str->end = end;

    return str;
}

orca_Int_t *orca_Int_new(int64_t value) {
    orca_Int_t *intg = orca_xmalloc(sizeof(orca_Int_t));

    intg->value = value;

    return intg;
}
