#include <dirent.h>
#include <stdio.h>
#include <string.h>

int search_directory(const char *dirname, const char *subdirname) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory specified by dirname
    dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return -1;
    }

    // Read the contents of the directory
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a subdirectory
        if (entry->d_type == DT_DIR) {
            // Ignore the "." and ".." directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // Check if the subdirectory name matches the one we're searching for
            if (strcmp(entry->d_name, subdirname) == 0) {
                // We found the subdirectory we were looking for, so close the directory and return success
                closedir(dir);
                return 0;
            }

            // Recursively search the subdirectory
            if (search_directory(entry->d_name, subdirname) == 0) {
                // We found the subdirectory we were looking for in a subdirectory, so close the directory and return success
                closedir(dir);
                return 0;
            }
        }
    }

    // We didn't find the subdirectory we were looking for, so close the directory and return failure
    closedir(dir);
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <dirname> <subdirname>\n", argv[0]);
        return 1;
    }

    const char *dirname = argv[1];
    const char *subdirname = argv[2];

    if (search_directory(dirname, subdirname) == 0) {
        printf("Found subdirectory '%s' in directory '%s'\n", subdirname, dirname);
    } else {
        printf("Could not find subdirectory '%s' in directory '%s'\n", subdirname, dirname);
    }

    return 0;
}
