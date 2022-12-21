#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char** argv) {
  char* json_string = "{\"key\":\"value\"}";
  json_object* json = json_tokener_parse(json_string);

  if (json == NULL) {
    printf("Invalid JSON\n");
  } else {
    printf("Valid JSON\n");
  }

  return 0;
}
