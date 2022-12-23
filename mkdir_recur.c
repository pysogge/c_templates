// Not working


#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

int mkdir_p(const char *path) {
  if (path == NULL) {
    // Invalid path
    errno = EINVAL;
    return 1;
  }

  // Make a copy of the path
  char *copy = strdup(path);
  if (copy == NULL) {
    // Error allocating memory
    errno = ENOMEM;
    return 1;
  }

  // Split the path into components
  char *component = copy;
  char *next;
  while ((next = strchr(component, '/')) != NULL) {
    // Split the component from the path
    *next = '\0';

    if (*component == '\0') {
      // Skip empty component (path starts with '/')
      component = next + 1;
      continue;
    }

    // Create the component if it does not exist
    if (mkdir(copy, 0777) == -1) {
      if (errno != EEXIST && errno != ENOTDIR) {
        // An error occurred while creating the directory
        perror("Error creating directory");
        free(copy);
        return 1;
      }
    }

    // Advance to the next component
    component = next + 1;
  }

  if (*component == '\0') {
    // Skip empty component (path ends with '/')
    free(copy);
    return 0;
  }

  // Create the last component if it does not exist
  if (mkdir(copy, 0777) == -1) {
    if (errno != EEXIST && errno != ENOTDIR) {
      // An error occurred while creating the directory
      perror("Error creating directory");
      free(copy);
      return 1;
    }
  }

  // Free the copy of the path
  free(copy);

  // All components were created successfully
  return 0;
}

int main(int argc, char *argv[]) {
  // Define the path to create
  char *path = "/tmp/dir1/dir2/dir3";

  // Create the directory
  int result = mkdir_p(path);
  if (result == 0) {
    printf("Directory was created successfully\n");
  } else {
    printf("Error creating directory\n");
  }

  return result;
}

// This example program defines a function mkdir_p that takes a path as an argument and creates all the directories in the path. It uses the strdup function to make a copy of the path, and the strchr function to split the path into components. It then uses the mkdir function to create each component, starting from the root directory and working down the directory tree.