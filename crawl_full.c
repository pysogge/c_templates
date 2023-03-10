// ./crawl_full target_directory_name

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Check that a directory name was provided
    if (argc < 2) {
        fprintf(stderr, "Error: No directory name provided\n");
        return 1;
    }

    // Get the name of the directory to search for
    const char* target_dir_name = argv[1];

    // Allocate a buffer to hold the current working directory
    char full_path[1024];

    // Get the realpath of the arg[0] (the program name) and save it to full_path
    if (realpath(argv[0], full_path) == NULL) {
        perror("realpath");
        return 1;
    }

    char* current_dir = strdup(full_path);

    // Crawl up the directory tree of the full path until the lead directory matches the name of the target directory
    while (1) {
        // Get the leaf directory name of the current working directory, not including the leading or trailing '/'

        const char* current_dir_name = strrchr(current_dir, '/') + 1;
        
        if (current_dir_name == NULL) {
            fprintf(stderr, "Error: Could not get current directory name\n");
            return 1;
        }

        // If the current directory name matches the target directory name, then we're done
        if (strcmp(current_dir_name, target_dir_name) == 0) {
            break;
        }

        // If we've made it all the way up to "/", then the target directory was not found
        // return an error
        if (strcmp(current_dir, "/") == 0) {
            fprintf(stderr, "Error: Could not find directory '%s'\n", target_dir_name);
            return 1;
        }

        // move up one directory from full_path
        current_dir = strdup(dirname(current_dir));

        // printf("current_dir: %s\n", current_dir);

        // // Change to the parent directory
        // if (chdir("..") != 0) {
        //     perror("chdir");
        //     return 1;
        // }

        // // Get the realpath of the current working directory and save it to full_path
        // if (realpath(".", full_path) == NULL) {
        //     perror("realpath");
        //     return 1;
        // }

        // // check if a file path like /tmp/image.png is a real found file
        // if (access(full_path, F_OK) != -1) {
        //     printf("File %s exists and is a file.\n", full_path);
        // } else {
        //     printf("File %s does not exist.\n", full_path);
        // }

    }

    // Print the path of the target directory
    printf("Found directory: %s\n", current_dir);
    return 0;
}

// This program first checks that a directory name was provided on the command line. It then uses a loop to repeatedly change to the parent directory and check the current working directory until it finds the target directory.

// To use this program, you can compile it with a command like gcc crawl.c -o crawl and run it with a command like ./crawl target_directory_name (not full path). The program will crawl up the directory tree until it finds the directory with the specified name, and then print the path to that directory.