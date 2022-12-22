#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int remove_directories(char **directories, int num_directories) {
    for (int i = 0; i < num_directories; i++) {
        // Get the directory path
        char *path = directories[i];

        // Try to remove the directory
        if (rmdir(path) == -1) {
            // An error occurred while removing the directory
            perror(path);
            return 1;
        }
    }

    // All directories were removed successfully
    return 0;
}

int main(int argc, char *argv[]) {
    // Define the list of directories
    char *directories[] = {"/tmp/dir1", "/tmp/dir2", "/tmp/dir3"};
    int num_directories = sizeof(directories) / sizeof(directories[0]);

    // Remove the directories
    int result = remove_directories(directories, num_directories);
    if (result == 0) {
        printf("All directories were removed successfully\n");
    } else {
        printf("Error removing directories\n");
    }

    return result;
}

// This example program defines a function remove_directories that takes a list of directory paths and the number of directories as arguments. It iterates through the list and uses the rmdir function to delete each directory. If the rmdir function returns an error, the function uses the perror function to print an error message indicating which directory could not be removed.