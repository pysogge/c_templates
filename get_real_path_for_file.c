#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mount.h>

char *get_real_path(const char *path) {
    // Use realpath to resolve the path
    char *real_path = realpath(path, NULL);
    if (real_path == NULL) {
        // An error occurred while resolving the path
        perror("Error resolving path");
        return NULL;
    }

    // Use mount to get information about the mounted filesystem
    struct statfs fs_info;
    if (statfs(real_path, &fs_info) == -1) {
        // An error occurred while getting filesystem information
        perror("Error getting filesystem information");
        return NULL;
    }

    // Check if the filesystem is mounted
    if (strcmp(fs_info.f_mntfromname, "/dev/mmcblk02") == 0) {
        // The filesystem is mounted at /dev/mmcblk02
        // Construct the real absolute path for the file
        char *real_absolute_path = malloc(strlen(fs_info.f_mntfromname) + strlen(real_path) + 2);
        if (real_absolute_path == NULL) {
            // An error occurred while allocating memory
            perror("Error allocating memory");
            return NULL;
        }
        sprintf(real_absolute_path, "%s%s", fs_info.f_mntfromname, real_path);

        // Free the real path
        free(real_path);

        // Return the real absolute path
        return real_absolute_path;
    } else {
        // The filesystem is not mounted at /dev/mmcblk02
        // Return the real path as-is
        return real_path;
    }
}

int main(int argc, char *argv[]) {
    // Define the path to resolve
    char *path = "/mnt/mmc/mydir/file.txt";

    // Get the real path for the file
    char *real_path = get_real_path(path);
    if (real_path == NULL) {
        printf("Error getting real path for file %s.\n", path);
        return 1;
    } else {
        printf("Real path for file %s is %s.\n", path, real_path);
    }

    // Free the real path
    free(real_path);

    return 0;
}

// If you run the realpath function on the path "/mnt/mmc/mydir/file.txt" in a C program and the file is mounted at /dev/mmcblk02 as /mnt/mmc/mydir/file.txt, the realpath function will resolve the path to /mnt/mmc/mydir/file.txt.

// The realpath function resolves symbolic links and follows mount points to find the real absolute path for a file. In this case, the path "/mnt/mmc/mydir/file.txt" is an absolute path, and the realpath function will resolve it to the absolute path /mnt/mmc/mydir/file.txt without any additional processing.

// If you want to find the real absolute path for the file on the underlying filesystem, you will need to use a different approach. One option is to use the mount function from the sys/mount.h header to obtain information about the mounted filesystem, and then use this information to construct the real absolute path for the file.