#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int add(int a, int b) {
  return a + b;
}

int main(int argc, char *argv[]) {
  int result = add(2, 3);
  assert(result == 5);
  printf("Test passed.\n");
  exit(0);
}
