#ifndef ORCA_VM_GC_H
#define ORCA_VM_GC_H

#include "vm-object.h"
#include <stddef.h>

typedef struct {
    orca_Object_t **objs;
    size_t size;
    size_t cap;
} orca_object_tracker_t;

typedef struct {
    orca_object_tracker_t tracker;
} orca_gc_t;

void orca_object_tracker_init(orca_object_tracker_t *tracker);

void orca_object_tracker_destruct(orca_object_tracker_t *tracker);

void orca_object_tracker_add(orca_object_tracker_t *tracker, 
                                orca_Object_t *obj);

void orca_object_tracker_remove(orca_object_tracker_t *tracker, size_t i);

void orca_gc_init(orca_gc_t *gc);

void orca_gc_destruct(orca_gc_t *gc);

void orca_gc_track(orca_gc_t *gc, orca_Object_t *obj);

void orca_gc_cycle(orca_gc_t *gc);

#endif
