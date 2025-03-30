#include "text-iterator.h"
#include <assert.h>

void orca_text_iterator_init(orca_text_iterator_t *iter, char const *filename, 
                             char const *text) {
    orca_text_position_init(&iter->pos, filename);
    iter->text = text;
}

char orca_text_iterator_get(orca_text_iterator_t *iter) {
    assert(!orca_text_iterator_at_end(iter));

    return *iter->text;
}

char orca_text_iterator_next(orca_text_iterator_t *iter) {
    assert(!orca_text_iterator_at_end(iter));

    char c = *iter->text;
    if (c == '\n') {
        orca_text_position_next_line(&iter->pos);
    } else {
        orca_text_position_next_col(&iter->pos);
    }

    iter->text++;
    return *iter->text;
}

bool orca_text_iterator_at_end(orca_text_iterator_t *iter) {
    return *iter->text == '\0';
}
