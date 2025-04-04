#include "util.h"
#include "classify.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

void *orca_xmalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "malloc failed: size %ld\n", size);
        abort();
    }

    return p;
}

void *orca_xcalloc(size_t size) {
    void *p = calloc(size, 1);
    if (p == NULL) {
        fprintf(stderr, "calloc failed: size %ld\n", size);
        abort();
    }

    return p;
}

void *orca_xrealloc(void *p, size_t size) {
    assert(p != NULL);

    void *p2 = realloc(p, size);
    if (p2 == NULL) {
        fprintf(stderr, "realloc failed: size %ld\n", size);
        abort();
    }

    return p2;
}

char *orca_read_file(char const *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    size_t size = 0;
    size_t size_read = 0;
    size_t cap = 256;

    char *text = orca_xmalloc(cap);

    while ((size_read = fread(text + size, 1, cap - size, file)) > 0) {
        size += size_read;
        
        if (size + 1 > cap) {
            cap *= 2;
            text = orca_xrealloc(text, cap);    
        }
    }

    text[size] = '\0';
    fclose(file);

    return text;
}

void orca_context_line_write(char const *string, 
                             orca_text_position_t *start,
                             orca_text_position_t *end,
                             FILE *file) {
    assert(start->line == end->line);

    int size = end->col - start->col;

    char const *linestart = string - (start->col - 1);
    char const *lineend = string + size;
    while (!orca_is_newline(*lineend) && *lineend != '\0') {
        lineend++;
    }

    fprintf(file, "%6ld | %.*s\n       | ", 
            start->line, (int)(lineend - linestart), linestart);
    
    for (int i = 0; i < string - linestart; i++) {
        fprintf(file, " ");
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "^");
    }

    fprintf(file, "\n");
}

void orca_token_error(orca_token_t *token, char const *fmt, ...) {
    orca_text_position_t end = token->pos;
    orca_text_position_forward(&end, token->end - token->start);

    va_list args;
    va_start(args, fmt);
    orca_range_error_va(token->start, &token->pos, &end, fmt, args);
    va_end(args);
}

void orca_range_error(char const *string, 
                      orca_text_position_t *start, 
                      orca_text_position_t *end,
                      char const *fmt, ...) {    
    va_list args;
    va_start(args, fmt);
    
    fprintf(stderr, ORCA_ANSI_ERROR);

    orca_text_position_write(start, stderr);
    fprintf(stderr, ": ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    orca_context_line_write(string, start, end, stderr);

    fprintf(stderr, ORCA_ANSI_RESET);
    
    va_end(args);
}

void orca_range_error_va(char const *string, 
                         orca_text_position_t *start, 
                         orca_text_position_t *end,
                         char const *fmt, va_list args) {  
    fprintf(stderr, ORCA_ANSI_ERROR);
    
    orca_text_position_write(start, stderr);
    fprintf(stderr, ": ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    
    orca_context_line_write(string, start, end, stderr);

    fprintf(stderr, ORCA_ANSI_RESET);
}

void orca_char_repr(char c, FILE *file) {
    if (isprint(c)) {
        fprintf(file, "%c", c);
        return;
    }

    switch (c) {
        case '\n':  fprintf(file, "\\n");           break;
        case '\r':  fprintf(file, "\\r");           break;
        case '\t':  fprintf(file, "\\t");           break;
        default:    fprintf(file, "\\x%02X", c);    break;
    }
}

void orca_string_repr(char const *start, char const *end, FILE *file) {    
    for (char const *s = start; s != end; s++) {
        orca_char_repr(*s, file);
    }
}

void orca_write_n_chars(int n, char c, FILE *file) {
    for (int i = 0; i < n; i++) {
        putc(c, file);
    }
}

int64_t orca_string_to_int64(char const *start, char const *end) {
    int64_t res = 0;
    int64_t max_div_10 = INT64_MAX / 10;
    int64_t max_mod_10 = INT64_MAX % 10;
    
    for (const char *ptr = start; ptr < end; ++ptr) {
        if (*ptr == '_') continue;;

        assert (*ptr >= '0' && *ptr <= '9');
        
        int digit = *ptr - '0';
        if (res > max_div_10 || (res == max_div_10 && digit > max_mod_10)) {
            return -1;
        }
        
        res = res * 10 + digit;
    }
    
    return res;

}