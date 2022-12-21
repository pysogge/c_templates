#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Generates a string in the format "YYYYYMMDD-XXXXXXXX" where YYYYY represents the
// current year, MM represents the current month, DD represents the current day, and
// XXXXXXXX represents an 8-digit hexadecimal number generated using the rand function.
// The generated string is stored in the specified output buffer.
// Returns: 0 on success, -1 on error.
int generate_string(char *output) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (tm == NULL) {
        return -1;
    }

    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;

    sprintf(output, "%04d%02d%02d-", year, month, day); // format the year, month, and day

    // Generate a random 8-digit hexadecimal number and append it to the string
    for (int i = 0; i < 8; i++) {
        sprintf(output + strlen(output), "%x", rand() % 16);
    }

    return 0;
}

int main(void) {
    char str[20]; // string to store the result
    int result = generate_string(str);
    if (result == 0) {
        printf("String: %s\n", str);
    } else {
        printf("Error generating string!\n");
    }

    return 0;
}