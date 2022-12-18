#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // Invoke the binary with multiple arguments and run it in the background
  char command[1024];
  sprintf(command, "./binary arg1 arg2 &");
  int result = system(command);

  // Check the return value of system
  if (result == -1) {
    perror("system");
    return 1;
  }

  // Open the file that the binary writes to
  FILE *file = fopen("output.txt", "r");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  // Read from the file
  char line[1024];
  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line);
  }

  // Close the file
  fclose(file);

  return 0;
}
