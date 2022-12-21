#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_valid_json(const char* json_string) {
  enum state {
    STATE_START,
    STATE_KEY,
    STATE_COLON,
    STATE_VALUE,
    STATE_COMMA,
  };

  enum state current_state = STATE_START;
  int length = strlen(json_string);

  for (int i = 0; i < length; i++) {
    char c = json_string[i];
    switch (current_state) {
      case STATE_START:
        if (c == '{') {
          current_state = STATE_KEY;
        } else {
          return false;
        }
        break;
      case STATE_KEY:
        if (c == '"') {
          current_state = STATE_COLON;
        } else {
          return false;
        }
        break;
      case STATE_COLON:
        if (c == ':') {
          current_state = STATE_VALUE;
        } else {
          return false;
        }
        break;
      case STATE_VALUE:
        if (c == '"') {
          current_state = STATE_COMMA;
        }
        break;
      case STATE_COMMA:
        if (c == ',') {
          current_state = STATE_KEY;
        } else if (c == '}') {
          return true;
        } else {
          return false;
        }
        break;
    }
  }

  return false;
}

int main(int argc, char** argv) {
  char* json_string = "{\"key\":\"value\"}";
  if (is_valid_json(json_string)) {
    printf("Valid JSON\n");
  } else {
    printf("Invalid JSON\n");
  }
  return 0;
}
