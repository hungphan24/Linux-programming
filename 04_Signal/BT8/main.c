#include<stdio.h>
#include<signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Crash by signal = %d\n", sig);
}

void handler2(int sig) {
    printf("Hello from SIGUSR1\n");
}

void main() {

    signal(SIGINT, handler);
    signal(SIGUSR1, handler2);
    while (1)
    {
        printf("this is main thread\n");
        sleep(2);
    }

}