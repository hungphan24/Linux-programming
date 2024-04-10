#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define     MAX_STRING_LENGTH  50

pthread_t thread1, thread2, thread3;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct student {
    char name[MAX_STRING_LENGTH];
    char birth[MAX_STRING_LENGTH];

};

static struct student sd;
volatile bool isEnter = false;
volatile bool isSaveFile = false;
volatile bool isReadFile = true;

bool saveFile() {
    int fd;

    fd = open("students.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Can not open or create file");
        return false;
    }

    char buffer[MAX_STRING_LENGTH * 2];
    sprintf(buffer, "%s %s\n", sd.name, sd.birth);
    if (write(fd, buffer, strlen(buffer)) == -1) {
        perror("error occur when write to file");
        return false;
    }

    if (close(fd) == -1) {
        perror("rror occur when close file");
        return false;
    }

    return true;

}

char* readFromFile() {
    int fd;
    char buffer[MAX_STRING_LENGTH];
    ssize_t bytesRead;

    fd = open("students.txt", O_RDONLY);
    if (fd == -1) {
        perror("can not open file");
        exit(EXIT_FAILURE);
    }

    char* content = (char*)malloc(1);
    content[0] = '\0';

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        content = (char*)realloc(content, strlen(content) + bytesRead + 1);
        strncat(content, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("error when read file");
        exit(EXIT_FAILURE);
    }

    // Đóng file
    if (close(fd) == -1) {
        perror("error when close file");
        exit(EXIT_FAILURE);
    }

    return content;
}

void *handler1(void *arg) {
    while (1)
    {
        if(isReadFile) {
            pthread_mutex_lock(&mtx);
            printf("Enter student name: ");
            scanf("%s", sd.name);

            printf("Enter birth: ");
            scanf("%s", sd.birth);

            isReadFile = false;
            isEnter = true;

            pthread_mutex_unlock(&mtx);
        }   

    }   
}


void * handler2(void* arg) {
    while(1) {
        if(isEnter) {
            pthread_mutex_lock(&mtx);
            (void)saveFile();
            isSaveFile = true;
            isEnter = false;
            pthread_mutex_unlock(&mtx);
        }
    }
}

void *handler3(void* arg) {
    while (1)
    {
        if(isSaveFile) {
            pthread_mutex_lock(&mtx);
            char *fileContent = readFromFile();
            printf("\n Content of file:\n%s\n", fileContent);
    
            free(fileContent);
            isSaveFile = false;
            isReadFile = true;

            pthread_mutex_unlock(&mtx);
        }
    }
    
}

void main() {

    pthread_create(&thread1, NULL, handler1, NULL);
    pthread_create(&thread2, NULL, handler2, NULL);
    pthread_create(&thread3, NULL, handler3, NULL);

    while(1) {}

}