#ifndef STACK_H
#define STACK_H
#define MAZESIZE 10
struct cell {
bool left, right, up, down;
char val;
bool visited;
int row,colum;
};

struct Node{
 cell data;
 Node *next;
};

struct Stack{
 Node *head;
 void push(cell);
 cell pop();
 bool isempty();
 void create();
 void close();

};

#endif // STACK_H
