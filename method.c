#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Run the computer vision inference binary and save the output to a string
  char output[1024];
  int status = system("/path/to/inference_binary -i /path/to/input.jpg > output.txt");
  if (status == -1) {
    printf("Error running system command\n");
    return 1;
  }

  // Read the output.txt file and check for object detection
  FILE *file = fopen("output.txt", "r");
  if (file == NULL) {
    printf("Error opening output.txt\n");
    return 1;
  }
  while (fgets(output, sizeof(output), file) != NULL) {
    if (strstr(output, "Object detected") != NULL) {
      // Call programs to convert the resulting images and collect device metadata
      status = system("/path/to/image_conversion_program /path/to/input.jpg /path/to/output.png");
      if (status == -1) {
        printf("Error running image conversion program\n");
      }
      status = system("/path/to/metadata_collection_program");
      if (status == -1) {
        printf("Error running metadata collection program\n");
      }
      break;
    }
  }
  fclose(file);
  return 0;
}
