#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
        return 1;
    }

    // Create the directory
    int result = mkdir(argv[1], 0777);

    // Check the result
    if (result == -1) {
        // An error occurred
        perror("Error creating directory");
        return 1;
    } else {
        // The directory was created successfully
        printf("Directory created successfully\n");
        return 0;
    }
}

// This example program takes the name of the directory to be created as a command-line argument. It then calls mkdir with this name and the permissions mode 0777, which gives read, write, and execute permissions to the owner, group, and other users. If mkdir returns -1, it means that an error occurred, and the program prints an error message using the perror function. Otherwise, it prints a success message.

// Note that the mkdir function is not available on all systems, so you may need to use a different function or method to create directories on some platforms.