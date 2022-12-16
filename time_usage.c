#include <stdio.h>
#include <time.h>

int main() {
    time_t start = time(NULL);
    // code to measure
    time_t end = time(NULL);
    double elapsed_time = difftime(end, start);
    printf("Wall-clock time used: %f seconds\n", elapsed_time);
    return 0;
}