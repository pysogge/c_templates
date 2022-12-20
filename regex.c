#include <stdio.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
  // Declare a regex_t structure to hold the compiled regex
  regex_t regex;

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
