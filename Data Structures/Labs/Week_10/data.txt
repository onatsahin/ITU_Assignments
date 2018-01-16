#ifndef DATA_H
#define DATA_H

struct nodeTree{
    int number, child;
    nodeTree* left;
    nodeTree* right;
};

struct node{
    nodeTree *data;
    node *next;
};

struct Tree{
    int Inorderfound;
    nodeTree *root;
    void createTree(int);
    void removeTree(nodeTree *);
    void InorderSearch(nodeTree*, int);
    void add(nodeTree*, int);
    int BFS(int);
    int DFS(int);
};

struct Stack{
    node *headStack;
    void push(nodeTree *);
    nodeTree* pop();
    bool isempty();
    void create();
    void close();
};

struct Que{
    node *headQue;
    node *backQue;
    int readTop();
    void enque(nodeTree *);
    nodeTree* deque();
    void create();
    void close();
    bool isemptyQue();
};

#endif // DATA_H
