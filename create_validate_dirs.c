#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int create_or_validate_directories(char **directories, int num_directories) {
  for (int i = 0; i < num_directories; i++) {
    // Get the directory path
    char *path = directories[i];

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
      // The directory exists, check if it is a directory and if it has write permissions
      if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: %s is not a directory\n", path);
        return 1;
      }
      if ((st.st_mode & S_IWUSR) == 0) {
        fprintf(stderr, "Error: %s does not have write permissions\n", path);
        return 1;
      }
    }
  }

  // All directories were created or validated successfully
  return 0;
}

int main(int argc, char *argv[]) {
  // Define the list of directories
  char *directories[] = {"/tmp/dir1", "/tmp/dir2", "/tmp/dir3"};
  int num_directories = sizeof(directories) / sizeof(directories[0]);

  // Create or validate the directories
  int result = create_or_validate_directories(directories, num_directories);
  if (result == 0) {
    printf("All directories were created or validated successfully\n");
  } else {
    printf("Error creating or validating directories\n");
  }

  return result;
}

// This example program defines a function create_or_validate_directories that takes a list of directory paths and the number of directories as arguments. It iterates through the list and uses the stat function to check the properties of each directory. If the stat function returns an error and the error is that the directory does not exist, the function creates the directory using the mkdir function. If the stat function returns an error