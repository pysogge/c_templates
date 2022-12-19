// does not handle lists

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main(void) {

    // get a string that is the full path of ../build and save it to full_path
    char full_path[1000];
    char *path = "../build";
    realpath(path, full_path);

    // get a string that is the full path of ../build/config.yml
    char full_path_config[1000];
    char *path_config = "../build/config.yml";
    realpath(path_config, full_path_config);

    // append filename onto full_path_config
    char full_path_config_filename[1000];
    strcpy(full_path_config_filename, full_path_config);
    


    // Open the config file
    FILE* config_file = fopen("config.yml", "r");
    if (config_file == NULL) {
        fprintf(stderr, "Error opening config file\n");
        return 1;
    }

    // Read the config file line by line
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, config_file) != NULL) {
        // if line is empty, or begins with a comment, skip it
        if (buffer[0] == '\n' || buffer[0] == '#') {
            continue;
        }

        // if line does not contain a colon or a dash, skip it
        if (strchr(buffer, ':') == NULL && strchr(buffer, '-') == NULL) {
            continue;
        }

        // // if the first non-whitespace character is a - this is a list item
        // // capture the key and the - together as the key, e.g. "- name"
        // // if the first non-whitespace character is not a -, this is not a list item
        // // capture the key as normal, e.g. "name"
        // if (strchr(buffer, '-') == NULL) {
        //     // if this is not a list item, do not include the "-" in the key
        //     // Split the line into key and value
        //     char* key = strtok(buffer, ":");
        //     char* value = strtok(NULL, ":");
        //     // Trim leading and trailing whitespace from key and value
        //     key = strtok(key, " ");
        //     value = strtok(value, " \n");

        //     // Store the key-value pair
        //     printf("Key: '%s', Value: '%s'\n", key, value);
        // } else {

        //     // if line does not contain a colon , set the key to "-"
        //     // and set the value to the rest of the line
        //     // if the value is empty skip it
        //     if (strchr(buffer, ':') == NULL) {
        //         char* key = strtok(buffer, "-");
        //         char* value = strtok(NULL, "-");
        //         // Trim leading and trailing whitespace from key and value
        //         key = strtok(key, " ");
        //         value = strtok(value, " \n");

        //         // Store the key-value pair
        //         printf("Key: '%s', Value: '%s'\n", key, value);
        //         continue;
        //     }


        //     // else if this is a list item with both - and "", include the "-" in the key
        //     // get everything up to the first -
        //     char* keydash = strtok(buffer, "-");
        //     // get everything after the first - up to the first :
        //     char* key = strtok(NULL, ":");

        //     // get everything after the first : up to the first \n
        //     char* value  = strtok(NULL, "\n");

        //     // Trim leading and trailing whitespace from key and value
        //     key = strtok(key, " ");
        //     value = strtok(value, " \n");

        //     // Store the key-value pair
        //     printf("Key: -'%s', Value: '%s'\n", key, value);
        // }


        // if this is not a list item, do not include the "-" in the key
        // Split the line into key and value
        char* key = strtok(buffer, ":");
        char* value = strtok(NULL, ":");
        // Trim leading and trailing whitespace from key and value
        key = strtok(key, " ");
        value = strtok(value, " \n");

        // Store the key-value pair
        printf("Key: '%s', Value: '%s'\n", key, value);
    }

    // Close the config file
    fclose(config_file);

    return 0;
}
