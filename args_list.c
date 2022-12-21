#include <stdarg.h>
#include <stdio.h>

int my_vsprintf(char *str, const char *format, ...) {
    va_list args;
    int ret;

    va_start(args, format);
    ret = vsprintf(str, format, args);
    va_end(args);

    return ret;
}

// The va_list type is used to store a list of arguments of an unknown number and type. The va_start macro initializes a va_list object and sets it to the first argument after the named arguments. The va_arg macro retrieves the next argument from the va_list object, and the va_end macro cleans up the va_list object and prepares it for reuse.

// The vsprintf function is a standard library function that is similar to sprintf, but it takes a va_list object as its argument instead of a fixed number of arguments. You can then use the vsprintf function to format the string with the variable arguments passed to your function.

// You can use this technique to create functions that take a variable number of arguments of any type. Just make sure to use the appropriate type when calling va_arg to retrieve the arguments from the va_list object.

int main(void) {
    char str[64];
    int result = my_vsprintf(str, "The numbers are %d, %d, and %d", 123, 456, 78910);
    if (result >= 0) {
        printf("String: %s (length: %d).\n", str, result);
    } else {
        printf("Error formatting string!\n");
    }

    return 0;
}