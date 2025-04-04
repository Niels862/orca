#include "classify.h"
#include <ctype.h>

bool orca_is_identifier_start(uint32_t c) {
    return isalpha(c) || c == '_';
}

bool orca_is_identifier_continue(uint32_t c) {
    return orca_is_identifier_start(c) || isdigit(c);
}

bool orca_is_integer_start(uint32_t c) {
    return isdigit(c);
}

bool orca_is_integer_continue(uint32_t c) {
    return isdigit(c) || c == '_';
}

bool orca_is_special(uint32_t c) {
    return orca_map_special(c) != ORCA_TOKEN_NONE;
}

bool orca_is_whitespace(uint32_t c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\t';
}

bool orca_is_comment_start(uint32_t c) {
    return c == '#';
}

bool orca_is_newline(uint32_t c) {
    return c == '\n';
}

orca_tokenkind_t orca_map_special(uint32_t c) {
    switch (c) {
        case '[':   return ORCA_TOKEN_LEFTBRACKET;
        case ']':   return ORCA_TOKEN_RIGHTBRACE;
        case '{':   return ORCA_TOKEN_LEFTBRACE;
        case '}':   return ORCA_TOKEN_RIGHTBRACE;
        case '(':   return ORCA_TOKEN_LEFTPAREN;
        case ')':   return ORCA_TOKEN_RIGHTBRACE;
        case ';':   return ORCA_TOKEN_SEMICOLON;
        case ',':   return ORCA_TOKEN_COMMA;
        case '.':   return ORCA_TOKEN_DOT;
        case '+':   return ORCA_TOKEN_PLUS;
        case '-':   return ORCA_TOKEN_MINUS;
        case '*':   return ORCA_TOKEN_ASTERISK;
        case '/':   return ORCA_TOKEN_SLASH;
        case '%':   return ORCA_TOKEN_PERCENT;
        case '<':   return ORCA_TOKEN_LESS_THAN;
        case '>':   return ORCA_TOKEN_GREATER_THAN;
        case '=':   return ORCA_TOKEN_EQUALS;
        case '!':   return ORCA_TOKEN_EXCLAMATION_MARK;
        case '|':   return ORCA_TOKEN_PIPE;
        case '&':   return ORCA_TOKEN_AMPERSAND;

        default:    return ORCA_TOKEN_NONE;
    }
}
