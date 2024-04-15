#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 2056

void parseInput(int argc, char const* argv[], char **ipAddress, int* port) {
    if(argc < 3) {
        printf("Please add ip address and port number of server\n");
        printf("Example: /client 127.168.0.1 8080");
    } else {
        *port = atoi(argv[2]);
        *ipAddress = strdup(argv[1]);
        printf("connect to server:ip: %s port = %d\n",ipAddress, *port);
    }
}

void main(int argc, char const* argv[]) {
    char* ipAddress;
    int port;
    int client_fd;
    struct sockaddr_in serv_addr;
    char sendMessage[MAX_BUFFER_SIZE] = { 0};
    char buffer[MAX_BUFFER_SIZE] = { 0 };
    parseInput(argc, argv, &ipAddress, &port);

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    printf("start2");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr);

    if ((connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
    }
    while(1) {
        printf("send message: ");
        memset(sendMessage, 0, MAX_BUFFER_SIZE);
        fgets(sendMessage, MAX_BUFFER_SIZE, stdin);
        send(client_fd, sendMessage, strlen(sendMessage), 0);

        printf("Received message: ");
        memset(buffer, 0, MAX_BUFFER_SIZE);
        read(client_fd, buffer, 1024 - 1);
        printf("%s\n", buffer);

    }

}