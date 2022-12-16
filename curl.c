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
