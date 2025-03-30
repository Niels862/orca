#ifndef ORCA_TEXT_POSITION_H
#define ORCA_TEXT_POSITION_H

#include <stdio.h>
#include <stddef.h>

typedef struct {
    char const *filename;
    size_t line;
    size_t col;
} orca_text_position_t;

void orca_text_position_init(orca_text_position_t *pos, char const *filename);

void orca_text_position_write(orca_text_position_t *pos, FILE *file);

void orca_text_position_next_line(orca_text_position_t *pos);

void orca_text_position_next_col(orca_text_position_t *pos);

void orca_text_position_forward(orca_text_position_t *pos, int n);

#endif
