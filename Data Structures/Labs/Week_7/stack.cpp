#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#include <iostream>
#include <cstring>
#include "stack.h"

void Stack::create(){
  head = NULL;
}

void Stack::close(){
  Node *p = head;
  while(head){
    p = head;
    head = head->next;
    delete p;
  }
}

bool Stack::isempty(){
  if(head==NULL)return true;
  else{
    return false;
  }
}
StackD Stack::pop(){
    Node *temp = head;
    StackD tempD;
    tempD = temp->data;
    head = head->next;
    delete temp;
    return tempD;
}
void Stack::push(StackD topush){
    Node *newnode = new Node;
    newnode->data = topush;
    newnode->next = head;
    head = newnode;
}
 
