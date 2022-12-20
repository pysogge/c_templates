#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[1024];
    char *substring = "specific substring";

    // Open the log file for reading
    fp = fopen("log.txt", "r");
    if (fp == NULL) {
        perror("Error opening log file");
        return 1;
    }

    // Loop indefinitely
    while (1) {
        // Read a line from the log file
        if (fgets(line, sizeof(line), fp) != NULL) {
            // Check if the line contains the specific substring
            if (strstr(line, substring) != NULL) {
                printf("Found specific substring: %s", line);

                // Close the log file
                fclose(fp);

                // Open the log file for writing
                fp = fopen("log.txt", "w");
                if (fp == NULL) {
                    perror("Error opening log file");
                    return 1;
                }

                // Write an empty string to the log file to clear its contents
                fprintf(fp, "");

                // Close the log file
                fclose(fp);

                // Open the log file for reading
                fp = fopen("log.txt", "r");
                if (fp == NULL) {
                    perror("Error opening log file");
                    return 1;
                }

            }
        }

        // Sleep for a few seconds
        sleep(5);
    }

    // Close the log file
    fclose(fp);

    return 0;
}
