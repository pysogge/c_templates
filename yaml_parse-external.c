#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    yaml_parser_t parser;
    yaml_document_t document;

    FILE *input = fopen("config.yaml", "r");
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, input);

    if (!yaml_parser_load(&parser, &document)) {
        printf("Error: %s (line %d, column %d)\n", parser.problem, parser.problem_mark.line + 1, parser.problem_mark.column + 1);
        exit(EXIT_FAILURE);
    }

    yaml_node_t *node = yaml_document_get_root_node(&document);
    if (node->type != YAML_MAPPING_NODE) {
        printf("Error: The document must contain a mapping node (line %d, column %d)\n", parser.problem_mark.line + 1, parser.problem_mark.column + 1);
        exit(EXIT_FAILURE);
    }

    for (yaml_node_pair_t *pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++) {
        yaml_node_t *key = yaml_document_get_node(&document, pair->key);
        yaml_node_t *value = yaml_document_get_node(&document, pair->value);

        if (key->type != YAML_SCALAR_NODE) {
            printf("Error: The key must be a scalar node (line %d, column %d)\n", parser.problem_mark.line + 1, parser.problem_mark.column + 1);
            exit(EXIT_FAILURE);
        }

        if (value->type != YAML_SCALAR_NODE) {
            printf("Error: The value must be a scalar node (line %d, column %d)\n", parser.problem_mark.line + 1, parser.problem_mark.column + 1);
            exit(EXIT_FAILURE);
        }

        printf("%s: %s  ", key->data.scalar.value, value->data.scalar.value);
    }

    printf("Config file parsed successfully!\n");

    // print all of the config keys and values
    for (yaml_node_pair_t *pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++) {
        yaml_node_t *key = yaml_document_get_node(&document, pair->key);
        yaml_node_t *value = yaml_document_get_node(&document, pair->value);

        printf("%s: %s  ", key->data.scalar.value, value->data.scalar.value);
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    fclose(input);

    return 0;
}