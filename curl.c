#include <stdio.h>
#include <curl/curl.h>

size_t read_callback(char *buffer, size_t size, size_t nitems, void *userp) {
  // Open the file to be uploaded
  FILE *fp = fopen((char *)userp, "rb");
  if (fp == NULL) {
    return CURL_READFUNC_ABORT;
  }

  // Read data from the file and copy it to the buffer
  size_t nread = fread(buffer, size, nitems, fp);

  // Close the file
  fclose(fp);

  return nread;
}

int main(int argc, char *argv[]) {
  // Check for the required arguments
  if (argc != 3) {
    printf("Usage: %s URL FILE\n", argv[0]);
    return 1;
  }

  CURL *curl;
  CURLcode res;

  // Initialize cURL
  curl = curl_easy_init();
  if (curl) {
    // Set the URL and the PUT option
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_PUT, 1L);

    // Set the callback function and user data (the file to be uploaded)
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, argv[2]);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up
    curl_easy_cleanup(curl);
  }

  return 0;
}


// This code defines a read_callback function that reads data from a file and copies it to a buffer. The read_callback function is used as the CURLOPT_READFUNCTION callback for the curl_easy_setopt function, and the file to be uploaded is passed as the CURLOPT_READDATA user data.

// To use this code, you can compile it with a command like gcc -o putput put.c -lcurl, and then run it with a command like ./putput URL FILE, where URL is the URL of the server to receive the PUT request, and FILE is the path to the `.

// gcc to compile the code for macos M1 arm64 architecture
// gcc -arch arm64 -o putput put.c -lcurl
// ./putput http://localhost:8080/putput.txt putput.txt