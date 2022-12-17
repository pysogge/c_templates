#include <stdio.h>

int main() {
    // Open a stream to the binary /usr/bin/openssl
    FILE *stream char command[70];
    char a[] = "Encrypted data";
    int len;
    len = snprintf(command, sizeof(command), "/usr/bin/openssl aes-256-cbc -d -a -salt %s", a);
    if (if len <= sizeof(command)) {
        stream = popen(command, "r");
    }

    // Read the output of the binary
    char output[1024];
    while (fgets(output, sizeof(output), stream) != NULL) {
        printf("%s", output);
    }

    // Close the stream
    pclose(stream);

    return 0;
}


// In this example, the popen function is used to execute the binary located at /path/to/binary and open a stream to its standard output. The stream is then read using the fgets function, which reads a line of output at a time and stores it in the output buffer. The printf function is used to print the output to the console. Finally, the pclose function is used to close the stream.

// Note that the popen function is used to execute a command and read its output, but it does not allow you to pass input to the command or read its standard error output. If you need to pass input to the command or read its standard error output, you can use the popen function in combination with the dup2 function from the unistd.h library to redirect the standard input and error streams
