#include <stdio.h>

#define MAX_LINE_LENGTH 1024

// Read a line of input from the file pointed to by fp, up to a maximum of max_length characters.
// The line is stored in the buffer pointed to by line, which must be at least max_length characters long.
// Returns the number of characters read, or -1 if an error occurred.
int read_line(FILE* fp, char* line, int max_length) {
    int i = 0;
    int c;
    while ((c = fgetc(fp)) != EOF && c != '\n' && i < max_length - 1) {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return (i > 0 || c != EOF) ? i : -1;
}

int main(int argc, char** argv) {
    // Open a file for reading
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    // Read lines from the file
    char line[MAX_LINE_LENGTH];
    while (read_line(fp, line, MAX_LINE_LENGTH) > 0) {
        printf("Line: %s", line);
    }

    // Close the file
    fclose(fp);
    return 0;
}
