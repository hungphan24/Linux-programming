#include<stdio.h>
#include <signal.h>
#include <unistd.h>


void signalHandler(int signum) {
    printf( "Received signal: %d", signum);;
}

void main() {
    
    signal(SIGINT, signalHandler);

    // Check if SIGINT is blocked
    sigset_t currentMask;
    sigemptyset(&currentMask);
    sigprocmask(SIG_BLOCK, NULL, &currentMask);
    if (sigismember(&currentMask, SIGINT)) {
        printf( "SIGINT is currently blocked.\n");
    } else {
        printf( "SIGINT is not currently blocked.\n" );
    }

    //block SIGINT 
    sigset_t blockMask;
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);
    sigprocmask(SIG_BLOCK, &blockMask, NULL); // add signal vao block mask (arg thu 2), ket qua duoc luu vao tham so thu 3

    sigemptyset(&currentMask);
    sigprocmask(SIG_BLOCK, NULL, &currentMask);
    if (sigismember(&currentMask, SIGINT)) {
        printf( "SIGINT is currently blocked.\n");
    } else {
        printf( "SIGINT is not currently blocked.\n" );
    }

}