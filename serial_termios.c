#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int fd;

    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        perror("Unable to open serial port");
        return 1;
    }

    struct termios options;

    if (tcgetattr(fd, &options) == -1) {
        perror("Unable to get serial port attributes");
        return 1;
    }

    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    if (tcsetattr(fd, TCSANOW, &options) == -1) {
        perror("Unable to set serial port attributes");
        return 1;
    }

    char *command = "AT\r";

    if (write(fd, command, strlen(command)) == -1) {
        perror("Unable to write to serial port");
        return 1;
    }

    char response[256];
    int n = read(fd, response, sizeof(response));

    if (n == -1) {
        perror("Unable to read from serial port");
        return 1;
    }

    printf("Response: %s\n", response);

    if (close(fd) == -1) {
        perror("Unable to close serial port");
        return 1;
    }
}
