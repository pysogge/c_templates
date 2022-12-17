#include <stdio.h>

int add(int a, int b) {
  return a + b;
}

int main(int argc, char **argv) {
  int num_tests_failed = 0;

  // Test that add returns the correct result
  int result = add(1, 2);
  if (result != 3) {
    printf("Test failed: add returned incorrect result\n");
    num_tests_failed++;
  }

  if (num_tests_failed == 0) {
    printf("All tests passed\n");
  } else {
    printf("%d tests failed\n", num_tests_failed);
  }

  return num_tests_failed;
}