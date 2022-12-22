#include <regex.h>
#include <stdio.h>
#include <string.h>

int is_filepath(const char *str) {
  // Define the regular expression pattern to match
  // This pattern matches a string that looks like a filepath
  char *pattern = "^(/[^/ ]*)+/?$";

  // Compile the regular expression pattern
  regex_t regex;
  int result = regcomp(&regex, pattern, REG_EXTENDED);
  if (result != 0) {
    char error_message[100];
    regerror(result, &regex, error_message, sizeof(error_message));
    fprintf(stderr, "Error compiling regular expression: %s\n", error_message);
    return 0;
  }

  // Match the regular expression pattern against the string
  result = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (result != 0) {
    // The string does not match the pattern, return 0
    return 0;
  } else {
    // The string matches the pattern, return 1
    return 1;
  }
}

int main(int argc, char *argv[]) {
  // Define the filepaths to test
  char *paths[] = {
    "/tmp/myfile.txt",  // a valid filepath
    "/tmp/mydir/",      // a valid filepath
    "/tmp/my file.txt", // an invalid filepath (contains a space)
    "tmp/myfile.txt",   // an invalid filepath (missing leading slash)
    "/tmp/myfiletxt",   // an invalid filepath (missing extension)
  };

  // Test the filepaths
  for (int i = 0; i < sizeof(paths) / sizeof(paths[0]); i++) {
    char *path = paths[i];
    if (is_filepath(path)) {
      printf("'%s' is a valid filepath (matches the pattern)\n", path);
    } else {
        printf("'%s' is not a valid filepath (does not match the pattern)\n", path);
        }
    }

    return 0;
}

