#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define    MAX_SIZE_BUFFER 80

void main() {
    int fd;
    char* fifoPath = "/tmp/fifo1";

    mkfifo(fifoPath, 0666);

    char readMessage[MAX_SIZE_BUFFER];
    fd = open(fifoPath, O_RDWR);
    while (1)
    {       
        read(fd, readMessage, sizeof(readMessage));
        printf("Received message: %s", readMessage);
    
    }
    close(fd);    
    
}