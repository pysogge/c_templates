#include <stdio.h>
#include <string.h>

int run_command_and_find_substring(const char *command, const char *substring) {
    // Execute the command and open a stream for reading the output
    FILE *stream = popen(command, "r");
    if (stream == NULL) {
        perror("Error executing command");
        return 1;
    }

    // Read the output line by line
    char line[1024];
    while (fgets(line, sizeof(line), stream) != NULL) {
        // Check if the substring is found in the line
        if (strstr(line, substring) != NULL) {
            // The substring was found, close
            // the stream and return success
            pclose(stream);
            return 0;
        }
    }

    // The substring was not found, close the stream
    // and return failure
    pclose(stream);
    return 1;
}

int main(int argc, char *argv[]) {
    // Define the command and substring
    char *command = "ls -l";
    char *substring = "file.txt";

    // Run the command and check if the substring is found
    int result = run_command_and_find_substring(command, substring);
    if (result == 0) {
        printf("The substring was found\n");
    } else {
        printf("The substring was not found\n");
    }

    return result;
}

// This example program defines a function run_command_and_find_substring that takes a command and a substring as arguments. It uses the popen function to execute the command and open a stream for reading the output. It uses the fgets function to read the output line by line and the strstr function to check if the substring is found in the line. If the substring is found, the function closes the stream and returns success. If the end of the output is reached without finding the substring, the function closes the stream and returns failure.