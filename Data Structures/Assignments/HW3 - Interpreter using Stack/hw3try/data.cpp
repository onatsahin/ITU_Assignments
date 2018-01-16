/*@Author
 * Student Name: Onat ŞAHİN
 * Student ID: sahino15
 * Student No: 150150129
 * Date : 24.12.2016
*/

#include <iostream>
#include <cstring>
#include "data.h"

//###### STACK ####################################################

void Stack::create(){
    head = NULL;
}

void Stack::close(){
    Node *p;
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
}

bool Stack::isempty(){
    return head == NULL;
}

char* Stack::pop(){
    Node *temp;
    char *tempstr = new char[10];

    temp = head;
    strcpy(tempstr, temp->data);
    head = head->next;
    delete temp;
    return tempstr;
}

void Stack::push(char* topush){
    Node *newnode = new Node;
    newnode->data = new char[10];
    newnode->arg = 0;
    strcpy(newnode->data, topush);
    newnode->next = head;
    head = newnode;
}

//### QUEUE #######################################################

void Queue::create(){
    front = NULL;
    back = NULL;
}

void Queue::close(){
    QNode *p;
    while(front){
        p = front;
        front = front->next;
        delete p;
    }
}

void Queue::enqueue(char* toadd){
    QNode *newnode = new QNode;
    newnode->data = new char[10];
    strcpy(newnode->data, toadd);
    newnode->next = NULL;

    if(isempty()){
        back = newnode;
        front = back;
    }
    else{
        back->next = newnode;
        back = newnode;
    }
}

char* Queue::dequeue(){
    QNode *frontnode;

    char* temp = new char[30];
    frontnode = front;
    strcpy(temp, frontnode->data);
    front = front->next;
    delete frontnode;
    return temp;
}

char* Queue::lookback(){
    return back->data;
}

bool Queue::isempty(){
    return front == NULL;
}



























