#ifndef STUDENT_H
#define STUDENT_H

#define MAXSTRING 40

//////////////////////////////
typedef struct {
    char name[MAXSTRING];
    int id;
}student;
//////////////////////////////
typedef struct _node* node;
struct _node{
    student data;
    node next;
};
//////////////////////////////
typedef struct _list* list;
struct _list{
    node head;
    node tail;
    int size;
};
/////////////////////////////
void printMenu();

list create_list_first();

void print(node s_node);

void printstudents(node head);

void load(char *filename,list l);

void save(char *filename,list l);

node addStudent(list l , int s_id , char* s_name);

node findStudent(node head,int s_id);

int deleteStudent(list l,int s_id);

void updateStudent(node head,int s_id,int new_id,char* new_name);

#endif