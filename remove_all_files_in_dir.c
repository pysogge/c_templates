#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int remove_files_in_directory(const char *directory) {
  // Open the directory
  DIR *dir = opendir(directory);
  if (dir == NULL) {
    perror(directory);
    return 1;
  }

  // Iterate over the files in the directory
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // Skip the "." and ".." entries
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // Construct the full path of the file
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

    // Try to remove the file
    if (unlink(path) == -1) {
      // An error occurred while removing the file
      perror(path);
      closedir(dir);
      return 1;
    }
  }

  // Close the directory
  closedir(dir);

  // All files were removed successfully
  return 0;
}

int main(int argc, char *argv[]) {
  // Define the directory
  char *directory = "/tmp/dir1";

  // Remove all files in the directory
  int result = remove_files_in_directory(directory);
  if (result == 0) {
    printf("All files in %s were removed successfully\n", directory);
  } else {
    printf("Error removing files in %s\n", directory);
  }

  return result;
}

// This example program defines a function remove_files_in_directory that takes a directory path as an argument. It uses the opendir function to open the directory and the readdir function to iterate over the files in the directory. For each file, it constructs the full path of the file using the snprintf function, and it uses the unlink function to delete the file. If the unlink function returns an error, the function uses the perror function to print an error message indicating which file could not be removed.