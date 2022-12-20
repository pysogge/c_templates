#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Declare a pointer to an integer and allocate enough memory for 10 integers
  int *array = malloc(10 * sizeof(int));

  // Check if the memory was successfully allocated
  if (array == NULL) {
    // If the memory was not successfully allocated, print an error message and exit
    printf("Error allocating memory\n");
    return 1;
  }

  // Use a loop to add values to the array
  for (int i = 0; i < 10; i++) {
    array[i] = i;
  }

  // Print the values in the array
  for (int i = 0; i < 10; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  // Reallocate the memory to increase the size of the array
  array = realloc(array, 20 * sizeof(int));

  // Check if the memory was successfully reallocated
  if (array == NULL) {
    // If the memory was not successfully reallocated, print an error message and exit
    printf("Error reallocating memory\n");
    return 1;
  }

  // Use a loop to add more values to the array
  for (int i = 10; i < 20; i++) {
    array[i] = i;
  }

  // Print the values in the array
  for (int i = 0; i < 20; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  // Free the memory when you are done with it
  free(array);

  return 0;
}

// This code will create a dynamically resizing array of integers and add values to it using a loop. It will then reallocate the memory to increase the size of the array and add more values to it. Finally, it will print the values in the array and free the memory when it is no longer needed.

// Note that when you use realloc, the memory may be moved to a new location in order to make room for the larger array. This means that the address of the array may change, so you should update the pointer to point to the new location of the array after calling realloc.