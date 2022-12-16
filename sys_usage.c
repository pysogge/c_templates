#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        printf("Maximum resident set size used: %ld\n", usage.ru_maxrss);
    }
    return 0;
}
