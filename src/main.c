#include "lexer.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s [filename]\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    char *text = orca_read_file(filename);
    if (text == NULL) {
        fprintf(stderr, "could not open file: %s\n", filename);
        return 1;
    }

    orca_token_t *tokens = orca_lex(filename, text);
    if (tokens == NULL) {
        free(text);
        return 1;
    }

    orca_token_t *curr = tokens;
    while (1) {
        orca_token_write(curr, stderr);
        fprintf(stderr, "\n");

        if (curr->kind == ORCA_TOKEN_ENDSOURCE) {
            break;
        }
        curr++;
    }

    free(text);
    free(tokens);

    return 0;
}
