#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 4096

int main()
{
    int shm_fd;
    void *ptr;

    // Create the shared memory segment
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    // Set the size of the shared memory segment
    ftruncate(shm_fd, SHM_SIZE);

    // Map the shared memory segment to the process's address space
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write to the shared memory segment
    sprintf(ptr, "Hello from process 1!");

    // Unmap the shared memory segment
    munmap(ptr, SHM_SIZE);

    // Close the shared memory segment
    close(shm_fd);

    return 0;
}


// This example creates a shared memory segment with the name "my_shared_memory", sets its size to 4096 bytes, maps it to the process's address space, writes a message to it, and then unmaps and closes the shared memory segment.

// To access the shared memory segment from another process, you can use the same steps to open the "my_shared_memory" segment, map it to the process's address space, read and write to it, and then unmap and close it.

// Note that the shared memory segment must be created and opened with the same name in both processes in order for them to be able to access it. Also, the shared memory segment is created with read and write permissions, so both processes will be able to read and write to it.