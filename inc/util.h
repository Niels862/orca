#ifndef ORCA_UTIL_H
#define ORCA_UTIL_H

#include "token.h"
#include <stdarg.h>
#include <inttypes.h>
#include <stddef.h>

#define ORCA_UNUSED(p) (void)(p)

#define ORCA_ANSI_ERROR "\033[31m"
#define ORCA_ANSI_WARNING "\033[33m"
#define ORCA_ANSI_RESET "\033[0m"

void *orca_xmalloc(size_t size);

void *orca_xcalloc(size_t size);

void *orca_xrealloc(void *p, size_t size);

char *orca_read_file(char const *filename);

void orca_context_line_write(char const *string, 
                             orca_text_position_t *start,
                             orca_text_position_t *end,
                             FILE *file);

void orca_token_error(orca_token_t *token, char const *fmt, ...);

void orca_range_error(char const *string, orca_text_position_t *start, 
                      orca_text_position_t *end,
                      char const *fmt, ...);

void orca_range_error_va(char const *string, 
                         orca_text_position_t *start, 
                         orca_text_position_t *end,
                         char const *fmt, va_list args);

void orca_char_repr(char c, FILE *file);

void orca_string_repr(char const *start, char const *end, FILE *file);

int64_t orca_string_to_int64(char const *start, char const *end);

#endif
