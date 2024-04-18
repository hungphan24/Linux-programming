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

    char writeMessage[MAX_SIZE_BUFFER];

    fd = open(fifoPath, O_RDWR);
    while (1)
    {
        
        printf("Enter message: ");
        fgets(writeMessage, sizeof(writeMessage), stdin);
        write(fd, writeMessage, strlen(writeMessage)+1);
            
    }
    close(fd);
    unlink(fd);
    
}