#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int create_or_verify_directory(const char *path) {
  // Check the properties of the directory
  struct stat st;
  if (stat(path, &st) == -1) {
    // An error occurred, check if the error was that the directory does not exist
    if (errno == ENOENT) {
      // The directory does not exist, create it
      if (mkdir(path, 0777) == -1) {
        // An error occurred while creating the directory
        perror("Error creating directory");
        return 1;
      }
    } else {
      // An error occurred while checking the directory properties
      perror("Error checking directory properties");
      return 1;
    }
  } else {
    // The directory exists, check if it is a directory
    if (!S_ISDIR(st.st_mode)) {
      fprintf(stderr, "Error: %s is not a directory\n", path);
      return 1;
    }
  }

  // The directory was created or verified successfully
  return 0;
}

int main(int argc, char *argv[]) {
  // Define the directory path
  char *path = "/tmp/mydir";

  // Create or verify the directory
  int result = create_or_verify_directory(path);
  if (result == 0) {
    printf("Directory was created or verified successfully\n");
  } else {
    printf("Error creating or verifying directory\n");
  }

  return result;
}
