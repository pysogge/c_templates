#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Load the config file and read the paths
    char source_dir[1024], intermediate_dir[1024], output_dir[1024];
    FILE *file = fopen("/path/to/config.txt", "r");
    if (file == NULL) {
        printf("Error opening config.txt\n");
        return 1;
    }
    fgets(source_dir, sizeof(source_dir), file);
    fgets(intermediate_dir, sizeof(intermediate_dir), file);
    fgets(output_dir, sizeof(output_dir), file);
    fclose(file);

    // Remove newline characters from the paths
    source_dir[strcspn(source_dir, "\n")] = 0;
    intermediate_dir[strcspn(intermediate_dir, "\n")] = 0;
    output_dir[strcspn(output_dir, "\n")] = 0;

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
                        // Process the file from source and intermediate into output
                        char source_path[1024], intermediate_path[1024], output_path[1024];
                        sprintf(source_path, "%s/%s", source_dir, event->name);
                        sprintf(intermediate_path, "%s/%s", intermediate_dir, event->name);
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