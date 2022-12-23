#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>

char *get_mount_path(const char *dir_path) {
    // Use statvfs to get information about the mounted filesystem
    struct statvfs fs_info;
    if (statvfs(dir_path, &fs_info) == -1) {
        // An error occurred while getting filesystem information
        perror("Error getting filesystem information");
        return NULL;
    }

    // Check if the filesystem is mounted
    if (fs_info.f_type != 0) {
        // The filesystem is mounted
        // Construct the real absolute mount path
        char *mount_path = malloc(strlen(fs_info.f_mntonname) + 1);
        if (mount_path == NULL) {
            // An error occurred while allocating memory
            perror("Error allocating memory");
            return NULL;
        }
        strcpy(mount_path, fs_info.f_mntonname);

        // Return the mount path
        return mount_path;
    } else {
        // The filesystem is not mounted
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    // Define the directory path to check
    char *dir_path = "/mnt/mmc";

    // Get the mount path for the directory
    char *mount_path = get_mount_path(dir_path);
    if (mount_path != NULL) {
        printf("Directory is mounted at %s.\n", mount_path);
    } else {
        printf("Directory is not mounted.\n");
    }

    // Free the mount path
    free(mount_path);

    return 0;
}
