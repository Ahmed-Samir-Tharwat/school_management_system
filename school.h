#ifndef SCHOOL_H_INCLUDED
#define SCHOOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct birth {
    uint8 day;
    uint8 month;
    uint32 year;
}Birth;

typedef struct data {
    uint8 name[20];
    uint8 address[20];
    uint8 phone_num[12];
    uint32 id;
    uint8 c_science_score;
    Birth birth_date;
}Data;

typedef struct student_node {
    Data student_data;
    struct student_node *next;
}student_node;

typedef struct l_list {
    student_node *head;
    uint32 Size;
}List;

void CREATE_LIST(List *list_ptr);
void MAIN_MENU(List *list_ptr);
boolean ADD_STUDENT(List *list_ptr);
char* DELETE_STUDENT(List *list_ptr);
void EDIT_STUDENT_DATA(List *list_ptr);
void UPDATE_ALL_SCORES(List *list_ptr);
void RANK_STUDENTS(List *list_ptr);

#endif
