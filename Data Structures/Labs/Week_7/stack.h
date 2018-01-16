#ifndef STACK_H
#define STACK_H
typedef struct d{
    int x;
    int y;
    int right;
    int left;
    int down;
    int up;
    int camefrom;
}StackD,position;


struct Node{
  StackD data;
  Node *next;
};

struct Stack{
  Node *head;
  void create();
  void close();
  void push(StackD);
  StackD pop();
  bool isempty();
};

#endif
