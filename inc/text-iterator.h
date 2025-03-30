#ifndef ORCA_TEXT_ITERATOR_H
#define ORCA_TEXT_ITERATOR_H

#include "text-position.h"
#include <stdbool.h>

typedef struct {
    orca_text_position_t pos;
    char const *text;
} orca_text_iterator_t;

void orca_text_iterator_init(orca_text_iterator_t *iter, char const *filename, 
                             char const *text);

char orca_text_iterator_get(orca_text_iterator_t *iter);

char orca_text_iterator_next(orca_text_iterator_t *iter);

bool orca_text_iterator_at_end(orca_text_iterator_t *iter);

#endif
