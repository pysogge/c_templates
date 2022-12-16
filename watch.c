#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Read the source and output directory paths from the command line
    if (argc != 3) {
        printf("Usage: %s source_directory output_directory\n", argv[0]);
        return 1;
    }
    char *source_dir = argv[1];
    char *output_dir = argv[2];

    // Initialize inotify and create a watch for the source directory
    int fd = inotify_init();
    if (fd == -1) {
        printf("Error initializing inotify\n");
        return 1;
    }
    int wd = inotify_add_watch(fd, source_dir, IN_CREATE);
    if (wd == -1) {
        printf("Error adding watch for source directory\n");
        return 1;
    }

    // Allocate a buffer for reading inotify events
    char buffer[1024];

    while (1) {
        // Read inotify events
        int length = read(fd, buffer, sizeof(buffer));
        if (length == -1) {
            printf("Error reading inotify events\n");
            return 1;
        }

        // Process inotify events
        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_CREATE) {
                // A new file has been created in the source directory
                if (event->len > 0) {
                    // Fork a child process to process the file
                    pid_t pid = fork();
                    if (pid == 0) {
                        // This is the child process
                        // Process the file and move it from source to output
                        char source_path[1024], output_path[1024];
                        sprintf(source_path, "%s/%s", source_dir, event->name);
                        sprintf(output_path, "%s/%s", output_dir, event->name);
                        process_file(source_path, output_path);
                        rename(source_path, output_path);
                        exit(0);
                    }
                }
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }

    // Clean up inotify
    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}

// This code initializes inotify, creates a watch for the source directory, and then enters a loop to read inotify events. Whenever a new file is created in the source directory, the code forks a
