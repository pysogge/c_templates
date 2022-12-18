#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int c;
    char *input_file = NULL;
    char *output_file = NULL;

    while ((c = getopt(argc, argv, "i:o:")) != -1) {
        switch (c) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
                if (optopt == 'i' || optopt == 'o') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                }
                return 1;
            default:
                return 1;
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "Missing required argument: -i\n");
        return 1;
    }

    if (output_file == NULL) {
        fprintf(stderr, "Missing required argument: -o\n");
        return 1;
    }

    // Now you can use the input_file and output_file variables in your program

    return 0;
}
