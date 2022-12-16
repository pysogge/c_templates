#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // The ftok function is used to generate a unique key based on a file and a character. 
    key_t key = ftok("/tmp/binary.bin", 'R');
    int shmid = shmget(key, sizeof(binary), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Unable to create shared memory segment");
        return 1;
    }

    void *shm = shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("Unable to attach shared memory segment");
        return 1;
    }

    memcpy(shm, binary, sizeof(binary));

    if (shmdt(shm) == -1) {
        perror("Unable to detach shared memory segment");
        return 1;
    }
}
