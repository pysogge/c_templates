#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

typedef struct {
    char* buffer;
    size_t buffer_length;
    size_t position;
} json_parser_t;


#endif