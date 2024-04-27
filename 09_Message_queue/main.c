#include "inc/Menu.h"
#include "inc/student.h"
#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<signal.h>

static bool shouldExit = false;
static int option;

void input() {
    printf("\n Enter selection: ");
    scanf("%d", &option);
    while (getchar() != '\n');
}

void handler(int sig) {
    (void)deleteMessageQueue();
    exit(0);
    (void)sig;
}

int main() {
    signal(SIGINT, handler);

    if(initMessageQueue() != E_OK) {
        shouldExit = true;
    }

    while (!shouldExit)
    {
        displayMenu();
        input();
        switch (option)
        {
        case 1:
            if(saveStudentInfo() != E_OK) {
                shouldExit = true;
            }
            break;

        case 2:
            long id;
            printf("Enter student id: ");
            scanf("%ld", &id);
            if(findStudentById(id) != E_OK) {
                shouldExit = true;
            }
            break;
        case 3:
            if(showAllStudent() != E_OK) {
                shouldExit = true;
            }
            break;
        case 4:
            long stid;
            printf("Enter student id: ");
            scanf("%ld", &stid);
            if(deleteStudentById(stid) != E_OK) {
                shouldExit = true;
            }
            break;
        case 5:
            shouldExit = true;
            break;
        
        default:
            printf("Your selection is not exist!!");
            break;
        }
    }
    (void)deleteMessageQueue();

    return 0;
}