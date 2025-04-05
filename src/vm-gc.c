#include "vm-gc.h"
#include "util.h"
#include <stdlib.h>

void orca_object_tracker_init(orca_object_tracker_t *tracker) {
    tracker->size = 0;
    tracker->cap = 1024;
    tracker->objs = orca_xmalloc(tracker->cap * sizeof(orca_Object_t *));
}

void orca_object_tracker_destruct(orca_object_tracker_t *tracker) {
    free(tracker->objs);
}

void orca_object_tracker_add(orca_object_tracker_t *tracker, 
                                orca_Object_t *obj) {
    if (tracker->size >= tracker->cap) {
        tracker->cap *= 2;
        tracker->objs = orca_xrealloc(tracker->objs, 
                                      tracker->cap * sizeof(orca_Object_t *));
    }

    tracker->objs[tracker->size] = obj;
    tracker->size++;
}

void orca_object_tracker_remove(orca_object_tracker_t *tracker, size_t i) {
    tracker->objs[i] = tracker->objs[tracker->size - 1];
    tracker->objs[tracker->size - 1] = NULL;
    tracker->size--;
}

void orca_gc_init(orca_gc_t *gc) {
    orca_object_tracker_init(&gc->tracker);
}

void orca_gc_destruct(orca_gc_t *gc) {
    orca_object_tracker_destruct(&gc->tracker);
}

void orca_gc_track(orca_gc_t *gc, orca_Object_t *obj) {
    orca_object_tracker_add(&gc->tracker, obj);
}

void orca_gc_cycle(orca_gc_t *gc) {
    ORCA_UNUSED(gc);
}
