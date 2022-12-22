#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void print_interface_addresses(void) {
  // Get the list of network interfaces
  struct ifaddrs *ifaddr, *ifa;
  if (getifaddrs(&ifaddr) == -1) {
    perror("Error getting interface addresses");
    return;
  }

  // Iterate over the list of interfaces
  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    // Check the address family
    if (ifa->ifa_addr->sa_family == AF_INET) {
      // Get the IP address
      struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
      char *ip = inet_ntoa(addr->sin_addr);
      printf("Interface: %s, IP address: %s\n", ifa->ifa_name, ip);
    }
  }

  // Free the list of interfaces
  freeifaddrs(ifaddr);
}

int main(int argc, char *argv[]) {
  // Print the IP addresses of all interfaces
  print_interface_addresses();
  return 0;
}


// This example program defines a function print_interface_addresses that uses getifaddrs to get a list of all network interfaces. It then iterates over the list and looks for interfaces with an IPv4 address. For each interface with an IPv4 address, it uses the inet_ntoa function to convert the address to a string and prints the interface name and the IP address.