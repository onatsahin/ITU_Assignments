#include "stack.h"
#include <iostream>
#include <cstdio>
#include <ctime>


bool Stack::isempty(){
    return head == NULL;
}

void Stack::create(){
    head = NULL;
}
void Stack::close(){
    Node *p = head;
    while(head){
        head = head->next;
        delete p;
        p = head;
    }
}
cell Stack::pop(){
    cell tempD = head->data;
    Node *topop = head;
    head = head->next;
    delete topop;
    return tempD;
}
void Stack::push(cell topush){
    Node *newnode = new Node;
    newnode->data = topush;
    newnode->next = head;
    head = newnode;
}
