#include "student.h"
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stdlib.h>

static void printfStudentinfo(message* msg) {
    printf("%-10ld | %-20s | %-5d | %-30s | %-15s\n", (msg->priority), msg->sv.StudentName, 
        msg->sv.age, msg->sv.HomeTown, msg->sv.PhoneNumber);
}

static error_t sendToMsq(message* msg) {
    error_t ret = E_OK;
    if(msgsnd(msgid, msg, sizeof(*msg), 0) == -1) {
        printf("Can not send message to message queue\n");
        ret = E_ERROR;
    }
    return ret;
}

int getMessageCount() {
    struct msqid_ds buf;
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(1);
    }
    return buf.msg_qnum;
}

error_t initMessageQueue() {
    error_t ret = E_OK;
    key_t key = ftok(pathName, prj_id);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1) {
        printf("Error in creating queue\n");
        ret = E_ERROR;
    }
    return ret;

}

error_t deleteMessageQueue() {
    error_t ret = E_OK;
    msgctl(msgid, IPC_RMID, NULL); 
    return ret;
}

error_t saveStudentInfo() {
    error_t ret = E_OK;
    struct sinhvien sv;
    struct message msg;

    printf("Enter name: ");
    fgets(sv.StudentName, sizeof(sv.StudentName), stdin);

    printf("Enter age: ");
    scanf("%d", &sv.age);

    while (getchar() != '\n');

    printf("Enter hometown: ");
    fgets(sv.HomeTown, sizeof(sv.HomeTown), stdin);

    printf("Enter Phone number: ");
    fgets(sv.PhoneNumber, sizeof(sv.PhoneNumber), stdin);

    msg.priority = id;
    msg.sv = sv;
    id++;

    ret = sendToMsq(&msg);
    return ret;
}

error_t findStudentById(const long stid) {
    message msg;
    error_t ret = E_OK;

    if (msgrcv(msgid, &msg, sizeof(msg), stid, IPC_NOWAIT) < 0) {
        perror("error find student");
        ret = E_ERROR;
    } else {
        printfStudentinfo(&msg);
        sendToMsq(&msg);
    }

    return ret;
}

error_t showAllStudent() {
    error_t ret = E_OK;
    message msg;
    int numberOfMessages = getMessageCount();

    for(int i = 1; i <= numberOfMessages; i++) {
        if (msgrcv(msgid, &msg, sizeof(msg), i, IPC_NOWAIT) < 0) {
            perror("error show all student");
            ret = E_ERROR;
        } else {
            printfStudentinfo(&msg);
            sendToMsq(&msg);
        }

    }
    return ret;
}

error_t deleteStudentById(const long id) {
    message msg;
    error_t ret = E_OK;

    if (msgrcv(msgid, &msg, sizeof(msg), id, IPC_NOWAIT) < 0) {
        perror("error delete student");
        ret = E_ERROR;
    } 
    return ret;
}