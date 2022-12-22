#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Check the number of arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s interface\n", argv[0]);
    return 1;
  }

  // Get the interface name
  char *interface = argv[1];

  // Get the list of network interfaces
  struct ifaddrs *ifaddr, *ifa;
  if (getifaddrs(&ifaddr) == -1) {
    perror("Error getting interface addresses");
    return 1;
  }

  // Iterate over the list of interfaces
  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    // Check the interface name
    if (strcmp(ifa->ifa_name, interface) == 0) {
      // Check the address family
      if (ifa->ifa_addr->sa_family == AF_INET) {
        // Get the IP address
        struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
        char *ip = inet_ntoa(addr->sin_addr);
        printf("IP address: %s\n", ip);
        return 0;
      }
    }
  }

  // The interface was not found or does not have an IPv4 address
  fprintf(stderr, "Error: interface not found or does not have an IPv4 address\n");
  return 1;
}

// This example program takes the name of an interface as a command-line argument, and it uses getifaddrs to get a list of all network interfaces. It then iterates over the list and looks for an interface with the specified name. If it finds an interface with the right name, it checks the address family to make sure it is an IPv4 address, and then it uses the inet_ntoa function to convert the address to a string and print it. If the interface is not found or does not have an IPv4 address, the program prints an error message.