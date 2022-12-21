#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

struct json_parser{
    char* buffer;
    size_t buffer_length;
    size_t position;
};

