#include <stdio.h>
#include <string.h>

// fgets and sizeof are used to prevent buffer overflow

int main(void)
{
  char name[20];

  printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);
  // Remove the newline character at the end of the string
  name[strcspn(name, "\n")] = '\0';

  printf("Your name is %s\n", name);

  return 0;
}
