#include <stdio.h>

int main(void) {
    int result;

    result = rename("/path/to/old/file.txt", "/path/to/new/file.txt");
    if (result == 0) {
        printf("File moved and renamed successfully!\n");
    } else {
        printf("Error moving and renaming file!\n");
    }

    return 0;
}
