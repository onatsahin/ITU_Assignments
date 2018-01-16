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
void Stack::push(char newdata){
    Node *newnode = new Node;
    newnode->data = newdata;
    newnode->next = NULL;
    if(isempty()){
      head = newnode;
    }
    else{
    newnode->next = head;
    head  = newnode;
  }
}
char Stack::pop(){
    Node *temp = head;
    char temp_char;
    head = head->next;
    temp_char = temp->data;
    delete temp;
    return temp_char;
}

bool Stack::isempty(){
  if(head==NULL)return true;
  else{
    return false;
  }
}
