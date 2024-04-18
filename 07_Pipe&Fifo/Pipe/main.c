#include<stdio.h>
#include<unistd.h>

#define MAX_SIZE_BUFFER 20
void main() {
    int pipefd[2];
    int pid;
    char sendMessage[] = {"Hello wourld!!\n"};
    char receivedMessage[MAX_SIZE_BUFFER];

    if(pipe(pipefd)) {
        printf("can not create pipe");
        exit(0);
    }

    pid = fork();
    
    if(pid == 0) {
        read(pipefd[0], receivedMessage, sizeof(receivedMessage));
        printf("Child Process - Message read from pipe:  %s\n", receivedMessage);
    } else {
        printf("Parent Process - Write to pipe - Message is %s\n", sendMessage);
        write(pipefd[1], sendMessage, sizeof(sendMessage));
    }
}