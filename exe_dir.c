#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *program_name = argv[0];
    char *program_dir = dirname(program_name);

    printf("Program directory (dirname): %s\n", program_dir);

    // win
    // char *program_name_2 = getexecname();
    // char *program_dir_2 = dirname(program_name_2);

    // printf("Program directory (getexecname): %s\n", program_dir_2);

    char *program_name_ = argv[0];
    char *program_path = realpath(program_name_, NULL);

    printf("Program path: %s\n", program_path);

    // ios
    // char path[1024];
    // uint32_t size = sizeof(path);
    // _NSGetExecutablePath(path, &size);

    // char *program_path = realpath(path, NULL);

    // printf("Program path: %s\n", program_path);

    return 0;
}
