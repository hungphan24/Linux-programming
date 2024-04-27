#ifndef STUDENT_H
#define STUDENT_H

#include<stdio.h>
#include <stdbool.h>
#include "error.h"

#define pathName   "test"
#define prj_id      100

static int msgid;
static long id = 1;

struct sinhvien {
	char StudentName[50];
	int age;
	char HomeTown[100];
	char PhoneNumber[100];
};

typedef struct message {
	long priority;
	struct sinhvien sv;
} message;

error_t initMessageQueue();
error_t saveStudentInfo(); 
error_t findStudentById(const long id);
error_t showAllStudent();
error_t deleteStudentById(const long id);
error_t deleteMessageQueue();



#endif  // STUDENT_H