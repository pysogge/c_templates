// main.c
// gcc main.c subroutine.c -o main.ex
// ./main.ex

// #include "data.h"
#include "subroutine.h"

int main(int argc, char** argv) {
    struct data d;
    d.value1 = 42;
    d.value2 = 3.14;
    // Use the fields of the data struct

    subroutine_function1(42, "hello");
    int result = subroutine_function2(3.14, "world");

    return 0;
}
