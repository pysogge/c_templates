#include <stdio.h>
#include <string.h>

int main() {
    char file_path[1024] = "/tmp/files/";
    int index;
    char new_path[1024];

    for (index = 0; index < 10; index++) {
        sprintf(new_path, "%s%08d.jpeg", file_path, index);
       
       printf("String: %s.\n", new_path);
    }
}