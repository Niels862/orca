#ifndef ORCA_CLASSIFY_H
#define ORCA_CLASSIFY_H

#include "token.h"
#include <inttypes.h>
#include <stdbool.h>

bool orca_is_identifier_start(uint32_t c);

bool orca_is_identifier_continue(uint32_t c);

bool orca_is_integer_start(uint32_t c);

bool orca_is_integer_continue(uint32_t c);

bool orca_is_special(uint32_t c);

bool orca_is_whitespace(uint32_t c);

bool orca_is_comment_start(uint32_t c);

bool orca_is_newline(uint32_t c);

orca_tokenkind_t orca_map_special(uint32_t c);

#endif
