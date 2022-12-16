#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    // code to measure
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Processor time used: %f seconds\n", elapsed_time);
    return 0;
}
