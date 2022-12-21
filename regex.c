#include <regex.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Declare a regex_t structure to hold the compiled regex
    regex_t regex;

    // A regex to capture number between \"index\": and ,
    

    // Compile the regex using regcomp
    int rc = regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);
    if (rc != 0) {
        // If there was an error compiling the regex, print an error message and exit
        printf("Error compiling regex\n");
        return 1;
    }

    // Declare a buffer to hold the string to be tested
    char string[1024];
    strcpy(string, "user@example.com");

    // Test the string against the compiled regex using regexec
    rc = regexec(&regex, string, 0, NULL, 0);
    if (rc == 0) {
        // If the string matches the regex, print a message
        printf("String matches regex\n");
    } else if (rc == REG_NOMATCH) {
        // If the string does not match the regex, print a message
        printf("String does not match regex\n");
    } else {
        // If there was an error executing the regex, print an error message
        printf("Error executing regex\n");
    }

    // Free the memory allocated for the compiled regex
    regfree(&regex);

    return 0;
}

// This code will compile the regex "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$" using regcomp, and then test the string "user@example.com" against the compiled regex using regexec. If the string matches the regex, it will print a message. If the string does not match the regex, it will print a different message. If there is an error executing the regex, it will print an error message.

// Note that the regex in this example is a regex that matches email addresses. You can use any regex that you desire in place of this regex. Just be sure to update the regex string in the regcomp function and the string to be tested in the regexec function as needed.