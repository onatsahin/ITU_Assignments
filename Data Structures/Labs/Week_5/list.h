#ifndef LIST_H
#define LIST_H
#include "node.h"

struct List{
Phone_node *head , *tail;
int personcount;
void create();
void close();
void makeEmpty();
void insert_person(char *);
void insert_number(char * ,char *, char *);
void remove_person(int ordernum);
void remove_number(int ordernum,char *);
int search(char *);
void update(int, char *);
void printall();
};
#endif
