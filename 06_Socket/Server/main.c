#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT_DEFAULT 8080
#define MAX_BUFFER_SIZE 2056
void parseInput(int argc, char const* argv[], int *port) {
    pid_t pid = getpid();
    if(argc < 2) {
        printf("Port number is empty. Default port = 8080\n");
    } else {
        printf("abcddd\n");
        *port = atoi(argv[1]);
        printf("server socket: port = %d\n", *port);
    }
}

void main(int argc, char const* argv[]) {
    int port = PORT_DEFAULT;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int opt = 1;
    int server_fd, client_socket;
    char buffer[MAX_BUFFER_SIZE] = { 0 };
    char response[MAX_BUFFER_SIZE] = { 0};

    parseInput(argc, argv, &port);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // allow any ip address
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((client_socket
            = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        } else {
            printf("connect success \n");
        }

    while(1) {
        printf("Received message: ");
        memset(buffer, 0, MAX_BUFFER_SIZE);
        read(client_socket, buffer,
                   1024 - 1);
        printf("%s\n", buffer);

        printf("Response message: ");
        memset(response, 0, MAX_BUFFER_SIZE);
        fgets(response, MAX_BUFFER_SIZE, stdin);
        send(client_socket, response, strlen(response), 0);

    }

    close(client_socket);
    close(server_fd);

}