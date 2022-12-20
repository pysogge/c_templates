#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int i = 0;

    // Loop indefinitely
    while (1) {
        // Print the current loop number and move the cursor back to the beginning of the line
        printf("Number of loops: %d\r", i);
        fflush(stdout);

        // Increment the loop counter and sleep for a second
        i++;
        sleep(1);
    }

    return 0;
}
