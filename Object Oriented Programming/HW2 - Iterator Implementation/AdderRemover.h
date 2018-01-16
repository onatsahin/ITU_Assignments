// Onat ŞAHİN No: 150150129
#ifndef ADDERREMOVER_H
#define ADDERREMOVER_H

#include <string>
#include <iostream>
using namespace std;

//#### NODE ###########################################

class Node{
    int data;
    Node *next;
    Node *prev;
public:
    Node();
    Node* getNext() const; //Get and Set functions are written to avoid defining friend classes
    void setNext(Node*);   //and have a more secure program
    Node* getPrev() const;
    void setPrev(Node*);
    int getData() const;
    void setData(int);
};

//#### TRAVERSERS ####################################

class ARTraverser{
protected:
    Node *current;
public:
    virtual ~ARTraverser(){}; //Destructors need to be virtual because we are managing derived class objects
    virtual bool hasNode()=0; //from base class pointers.
    virtual int next()=0;
    friend class AdderRemover;
    friend class FAFR;
    friend class FALR;
    friend class LAFR;
    friend class LALR;
};

class ARTF: public ARTraverser{
public:
    ~ARTF(){};
    bool hasNode();
    int next();
};

class ARTL: public ARTraverser{
public:
    ~ARTL(){};
    bool hasNode();
    int next();
};

//#### ADDER-REMOVERS ####################################

class AdderRemover{
protected:
    Node *head;
    Node *tail;
    string name;
    int nodeCount;
    ARTraverser *traverser;
public:
    AdderRemover();
    virtual ~AdderRemover(){};
    virtual void add(int)=0;
    virtual void remove()=0;
    virtual void setTraverser()=0;
    void display() const;
    void removeAll();
    void traverse() const;
};

class FAFR: public AdderRemover{
public:
    FAFR();
    ~FAFR();
    void add(int);
    void remove();
    void setTraverser();
};

class LALR: public AdderRemover{
public:
    LALR();
    ~LALR();
    void add(int);
    void remove();
    void setTraverser();
};

class FALR: public AdderRemover{
public:
    FALR();
    ~FALR();
    void add(int);
    void remove();
    void setTraverser();
};

class LAFR: public AdderRemover{
public:
    LAFR();
    ~LAFR();
    void add(int);
    void remove();
    void setTraverser();
};

#endif // ADDERREMOVER_H
