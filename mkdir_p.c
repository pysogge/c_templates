#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int mkdir_p(const char *path) {
    char *copypath = strdup(path);
    int i, len = strlen(copypath);
    for (i = 1; i < len; i++) {
        if (copypath[i] == '/') {
            copypath[i] = '\0';
            if (mkdir(copypath, 0777) != 0 && errno != EEXIST) {
                perror("mkdir");
                free(copypath);
                return -1;
            }
            copypath[i] = '/';
        }
    }
    if (mkdir(copypath, 0777) != 0 && errno != EEXIST) {
        perror("mkdir");
        free(copypath);
        return -1;
    }
    free(copypath);
    return 0;
}

int main(int argc, char **argv) {
    char *path = "/tmp/dir1/dir2/dir3";

    // Create the directory
    if (mkdir_p("/tmp/dir1/dir2") != 0) {
        // An error occurred
        return 1;
    } else {
        printf("Directory was created successfully\n");
    }

    return 0;
}
