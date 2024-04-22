#include <stdio.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#define     KEY              "hungphanduc"
#define     SHARE_MEM_SIZE    100

int main() {
    char sendMessage[] = "hello, I'm hungphan";
    key_t key = ftok(KEY, 65);

    int shmid = shmget(key, SHARE_MEM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1) {
        perror("create shared memory");
        return 1;
    }

    char* shareMem = (char*)shmat(shmid, (void*)0, 0);
    if (shareMem == (void *) -1) {
        perror("Shared memory attach");
        return 1;
    }

    strncpy(shareMem, sendMessage, SHARE_MEM_SIZE - 1);
    shareMem[SHARE_MEM_SIZE - 1] = '\0';
    printf("Message write to shareMem: %s\n", shareMem);

    shmdt(shareMem);
    return 0;
}