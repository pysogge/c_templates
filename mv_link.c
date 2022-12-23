#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int move_and_rename(const char *src, const char *dst) {
  // Create a hard link to the file
  if (link(src, dst) == -1) {
    // An error occurred while creating the link
    perror("Error creating link");
    return 1;
  }

  // Delete the original file
  if (unlink(src) == -1) {
    // An error occurred while deleting the file
    perror("Error deleting file");
    return 1;
  }

  // The file was moved and renamed successfully
  return 0;
}

int main(int argc, char *argv[]) {
  // Define the source and destination paths
  char *src = "/tmp/myfile.txt";
  char *dst = "/tmp/mydir/mynewfile.txt";

  // Move and rename the file
  int result = move_and_rename(src, dst);
  if (result == 0) {
    printf("File was moved and renamed successfully\n");
  } else {
    printf("Error moving and renaming file\n");
  }

  return result;
}
