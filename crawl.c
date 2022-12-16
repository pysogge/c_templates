#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
  // Check that a directory name was provided
  if (argc < 2) {
    fprintf(stderr, "Error: No directory name provided\n");
    return 1;
  }

  // Get the name of the directory to search for
  const char* target_dir = argv[1];

  // Allocate a buffer to hold the current working directory
  char cwd[1024];

  // Get the current working directory
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd");
    return 1;
  }

  // Crawl up the directory tree until the target directory is found
  while (strcmp(cwd, target_dir) != 0) {
    // Change to the parent directory
    if (chdir("..") != 0) {
      perror("chdir");
      return 1;
    }

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
      perror("getcwd");
      return 1;
    }
  }

  // Print the path of the target directory
  printf("Found directory: %s\n", cwd);
  return 0;
}

// This program first checks that a directory name was provided on the command line. It then uses a loop to repeatedly change to the parent directory and check the current working directory until it finds the target directory.

// To use this program, you can compile it with a command like gcc crawl.c -o crawl and run it with a command like ./crawl target_directory_name. The program will crawl up the directory tree until it finds the directory with the specified name, and then print the path to that directory.