#include<stdio.h>
#include <pthread.h>

#define     MAX_STRING_LENGTH  50
pthread_t thread_id1, thread_id2;

struct human {
    char name[MAX_STRING_LENGTH];
    int birth;
    char phoneNumber[MAX_STRING_LENGTH];
    char homeTown[MAX_STRING_LENGTH];
};

void *handler(void *vargp) {
    if(pthread_equal(pthread_self(), thread_id1)) {
        printf("I'm thread1 - Hello wourld \n");
    } else if(pthread_equal(pthread_self(), thread_id2)) {
        struct human person = *((struct human*)vargp);
        printf("Thread2: Name: %s  Year of birth: %d  \n", (person.name), (person.birth));
    }
}

void main() {
    struct human person;
    strcpy(person.name, "hungphan");
    person.birth = 24;
    

    pthread_create(&thread_id1, NULL, handler, NULL);
    pthread_create(&thread_id2, NULL, handler, (void *) &person);

    pthread_exit(NULL);
    
}