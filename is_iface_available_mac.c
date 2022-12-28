#include <net/if.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>

int is_interface_available(const char *interface_name) {
  struct ifaddrs *addrs, *tmp;
  int found = 0;

  // Get a linked list of network interfaces
  if (getifaddrs(&addrs) == -1) {
    perror("getifaddrs");
    return -1;
  }

  // Iterate through the list of interfaces
  tmp = addrs;
  while (tmp) {
    if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_LINK) {
      // Check if the interface name matches the one we're looking for
      if (strcmp(tmp->ifa_name, interface_name) == 0) {
        found = 1;
        break;
      }
    }

    tmp = tmp->ifa_next;
  }

  // Free the memory allocated by getifaddrs
  freeifaddrs(addrs);

  return found;
}


int main(int argc, char *argv[]) {
  // Define the interface name to check
  char *interface_name = "eth0";

  // Check if the interface is available
  if (is_interface_available(interface_name)) {
    printf("Interface %s is available on the system.\n", interface_name);
    } else {
    printf("Interface %s is not available on the system.\n", interface_name);
    }

    return 0;
}
