#include <stdio.h>

struct MyStruct {
  int data;
  void runServer() {
    printf("Running server...\n");
  }
};

int main() {
  struct MyStruct myStructInstance;
  myStructInstance.runServer();
  return 0;
}
