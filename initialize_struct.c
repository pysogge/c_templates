#include <stdlib.h>

struct person {
  char *name;
  int age;
};

struct person *create_person(char *name, int age) {
  // Allocate memory for the person struct
  struct person *p = malloc(sizeof(struct person));
  // Initialize the fields of the struct
  p->name = name;
  p->age = age;
  return p;
}

int main(int argc, char** argv) {
  // Create a new person instance
  struct person *p = create_person("Alice", 30);
  // Use the fields of the person struct
  printf("Name: %s\n", p->name);
  printf("Age: %d\n", p->age);
  // Don't forget to free the memory when you are done
  free(p);
  return 0;
}
