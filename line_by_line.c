#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Open the file for reading
  FILE *fp = fopen("file.txt", "r");

  // Declare a buffer for reading the lines of the file
  char line[1024];

  // Read each line of the file until the end is reached
  while (fgets(line, sizeof(line), fp)) {
    // Check if the line includes the substring "objects:"
    if (strstr(line, "objects:")) {
      // If the line includes the substring, print it
      printf("%s", line);
    }
  }

  // Close the file
  fclose(fp);

  return 0;
}
