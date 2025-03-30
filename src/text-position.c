#include "text-position.h"

void orca_text_position_init(orca_text_position_t *pos, char const *filename) {
    pos->filename = filename;
    pos->line = 1;
    pos->col = 1;
}

void orca_text_position_write(orca_text_position_t *pos, FILE *file) {
    fprintf(file, "%s:%ld:%ld", pos->filename, pos->line, pos->col);
}

void orca_text_position_next_line(orca_text_position_t *pos) {
    pos->line++;
    pos->col = 1;
}

void orca_text_position_next_col(orca_text_position_t *pos) {
    pos->col++;
}

void orca_text_position_forward(orca_text_position_t *pos, int n) {
    pos->col += n;
}