#ifndef DATA_H
#define DATA_H

struct Node{
    char *num;
    Node *next;
};

struct PhoneNode{
    char *name;
    PhoneNode *left;
    PhoneNode *right;
    Node *phonenum;
};

struct Tree{
    PhoneNode *root;
    void create();
    void close(PhoneNode *);
    PhoneNode *search(char*);
    void add(char *);
    void addNumber(char *,char *);
    void update(char *,char *);
    void deleteNum(char *);
    void deletePerson(char *);
    void PrintAll(PhoneNode*);
};


#endif // DATA_H
