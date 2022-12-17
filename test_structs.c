#include <stdio.h>
#include <stdlib.h>

struct ExampleStruct {
    int x;
    char *y;
};

struct ExampleStruct *create_example_struct(int x, char *y) {
    struct ExampleStruct *example = malloc(sizeof(struct ExampleStruct));
    example->x = x;
    example->y = y;
    return example;
}

int main(int argc, char **argv) {
    int num_tests_failed = 0;

    // Test that create_example_struct returns a valid struct
    struct ExampleStruct *example = create_example_struct(123, "hello");
    if (example == NULL) {
        printf("Test failed: create_example_struct returned NULL\n");
        num_tests_failed++;
    } else {
        // Test that the struct has the expected values
        if (example->x != 123) {
            printf("Test failed: example->x has incorrect value\n");
            num_tests_failed++;
        }
        if (strcmp(example->y, "hello") != 0) {
            printf("Test failed: example->y has incorrect value\n");
            num_tests_failed++;
        }
    }

    free(example);

    if (num_tests_failed == 0) {
        printf("All tests passed\n");
    } else {
        printf("%d tests failed\n", num_tests_failed);
    }

    return num_tests_failed;
}
