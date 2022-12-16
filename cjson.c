#include <json-c/json.h>
#include <stdio.h>

int is_valid_json(const char *json_string) {
    // Parse the JSON string
    json_object *json = json_tokener_parse(json_string);

    // Check if the JSON object is valid
    if (json == NULL) {
        // The JSON string is not valid
        return 0;
    }

    // The JSON string is valid
    json_object_put(json);
    return 1;
}

if (is_valid_json(json_string)) {
    printf("The string is a valid JSON string\n");
} else {
    printf("The string is not a valid JSON string\n");
}