#include <stdio.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#define     KEY              "hungphanduc"
#define     SHARE_MEM_SIZE    100

int main() {
    key_t key = ftok(KEY, 65);

    int shmid = shmget(key, SHARE_MEM_SIZE, 0666|IPC_CREAT);
    static pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
    if (shmid == -1) {
        perror("create shared memory");
        return 1;
    }

    char* shareMem = (char*)shmat(shmid, (void*)0, 0);
    if (shareMem == (void *) -1) {
        perror("Shared memory attach");
        return 1;
    }

    printf("Data read from memory: %s\n", shareMem);

    shmdt(shareMem);
    shmctl(shmid, IPC_RMID, NULL);
 
    return 0;
}