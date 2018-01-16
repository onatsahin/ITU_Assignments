/*@Author
 * Student Name: Onat ŞAHİN
 * Student ID: sahino15
 * Student No: 150150129
 * Date : 24.12.2016
*/

#ifndef DATA_H
#define DATA_H

struct Node{
    char* data;
    Node *next;
    int arg;
    int arglim;
};

struct QNode{
    char* data;
    QNode *next;
};

struct Stack{
    Node *head;

    void create();
    void push(char*);
    char* pop();
    bool isempty();
    void close();
};

struct Queue{
    QNode *front;
    QNode *back;
    void create();
    void close();
    void enqueue(char*);
    char* dequeue();
    char* lookback();
    bool isempty();
};

#endif
