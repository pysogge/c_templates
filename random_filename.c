#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void) {
    char str[20]; // string to store the result
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;

    sprintf(str, "%04d%02d%02d-", year, month, day); // format the year, month, and day

    // Generate a random 8-digit hexadecimal number and append it to the string
    for (int i = 0; i < 8; i++) {
        sprintf(str + strlen(str), "%x", rand() % 16);
    }

    printf("String: %s\n", str);

    return 0;
}
