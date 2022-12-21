#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

typedef struct {
    char* buffer;
    size_t buffer_length;
    size_t position;
} json_parser_t;

// Initializes a JSON parser with the given string
void json_parser_init(json_parser_t* parser, char* json_string) {
    parser->buffer = json_string;
    parser->buffer_length = strlen(json_string);
    parser->position = 0;
}

// Sets the position of the parser to the given index
void json_parser_set_position(json_parser_t* parser, size_t position) {
    parser->position = position;
}

// Returns the next token in the JSON string or NULL if there are no more tokens
char* json_parser_next_token(json_parser_t* parser) {
    if (parser->position >= parser->buffer_length) {
        return NULL;
    }

    char* token = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    int token_index = 0;

    char current_char = parser->buffer[parser->position];
    while (current_char != '\0' && current_char != ',' && current_char != ':' && current_char != '{' && current_char != '}') {
        token[token_index++] = current_char;
        parser->position++;
        current_char = parser->buffer[parser->position];
    }

    parser->position++;
    token[token_index] = '\0';
    return token;
}

// Get value of a given key
char* json_parser_get_value(json_parser_t* parser, char* key) {
    char* token;
    while ((token = json_parser_next_token(parser)) != NULL) {
        if (strcmp(token, key) == 0) {
            free(token);
            token = json_parser_next_token(parser);
            return token;
        }
        free(token);
    }
    return NULL;
}

// Destroy json parser
void json_parser_destroy(json_parser_t* parser) {
    free(parser->buffer);
}

int main(int argc, char** argv) {
    char* json_string = "{\"key1\":\"value1\",\"key2\":\"value2\"}";
    json_parser_t parser;
    json_parser_init(&parser, json_string);

    char* token;
    while ((token = json_parser_next_token(&parser)) != NULL) {
        printf("%s\n", token);
        free(token);
    }

    json_parser_init(&parser, json_string);

    char* value = json_parser_get_value(&parser, "key1");
    printf("Value of key1: %s\n", value);

    json_parser_destroy(&parser);

    return 0;
}

// This example defines a json_parser_t structure that holds the JSON string, its length, and the current position in the string. The json_parser_init function initializes the parser with the given string, and the json_parser_next_token function extracts the next token from the JSON string.

// In the main function, we create a JSON string and initialize a parser with it. Then, we loop through the tokens in the string using the json_parser_next_token function and print each one.