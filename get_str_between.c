#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char str[] = "The number is index:123, and that's it.";
    char *p = str;
    int num;

    p = strstr(p, "index:");  // find the start of the number
    if (p != NULL) {
        p += strlen("index:");  // move the pointer to the start of the number
        num = atoi(p);          // convert the number to an integer
        printf("Number: %d\n", num);
    } else {
        printf("Number not found!\n");
    }

    return 0;
}
