// Onat ŞAHİN No: 150150129
#include "AdderRemover.h"
using namespace std;

// NODE #########################################################

Node::Node(){
    next = NULL;
    prev = NULL;
}

Node* Node::getNext() const{
    return next;
}

void Node::setNext(Node *toSet){
    next = toSet;
}

Node* Node::getPrev() const{
    return prev;
}

void Node::setPrev(Node *toSet){
    prev = toSet;
}

int Node::getData() const{
    return data;
}

void Node::setData(int toSet){
    data = toSet;
}

// ADDER-REMOVER ##############################################################################

AdderRemover::AdderRemover(){
    head = NULL;
    tail = NULL;
    nodeCount = 0;
    traverser = NULL;
}

void AdderRemover::display() const{
    cout << name << " | NodeCount:" << nodeCount << endl << "------" << endl;

    Node *trav = head;

    if(nodeCount == 0){
        cout << "There is no element to print" << endl << endl;
        return;
    }

    while(trav){
        cout << trav->getData() << endl;
        trav = trav->getNext();
    }
    cout << endl;
}

void AdderRemover::removeAll(){
    while(head->getNext()){
        head = head->getNext();
        delete head->getPrev();
    }
    delete head;
    head = NULL;
    nodeCount = 0;
}

void AdderRemover::traverse() const{
    if(!traverser->hasNode()){
        cout << "ERROR: AdderRemover is empty or the traverser is not set" << endl << endl;
        return;
    }
    cout << name << " | NodeCount:" << nodeCount << endl << "------" << endl;

    while(traverser->hasNode()){
        cout << traverser->next() << endl;
    }
    cout << endl;
}

// FAFR ######################################################################################

FAFR::FAFR(){
    name = "FAFR";
}

FAFR::~FAFR(){
    removeAll();
    delete traverser;
}

void FAFR::add(int toAdd){
    Node *newNode = new Node;
    newNode->setData(toAdd);

    if(!head){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
    nodeCount++;
}

void FAFR::remove(){
    if(!head){
        cout << "FAFR is empty" << endl;
        return;
    }

    if(head->getNext()){
        head = head->getNext();
        delete head->getPrev();
        head->setPrev(NULL);
    }
    else{
        delete head;
        head = NULL;
        tail = NULL;
    }
    nodeCount--;
}

void FAFR::setTraverser(){
    if(!traverser)
        traverser = new ARTF;
    traverser->current = head;
}

// LALR #######################################################################################

LALR::LALR(){
    name = "LALR";
}

LALR::~LALR(){
    removeAll();
    delete traverser;
}

void LALR::add(int toAdd){
    Node *newNode = new Node;
    newNode->setData(toAdd);

    if(!head){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    nodeCount++;
}

void LALR::remove(){
    if(!head){
        cout << "FAFR is empty" << endl;
        return;
    }
    if(tail->getPrev()){
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNext(NULL);
    }
    else{
        delete tail;
        head = NULL;
        tail = NULL;
    }
    nodeCount--;
}

void LALR::setTraverser(){
    if(!traverser)
        traverser = new ARTL;
    traverser->current = tail;
}

// FALR #######################################################################################

FALR::FALR(){
    name = "FALR";
}

FALR::~FALR(){
    removeAll();
    delete traverser;
}

void FALR::add(int toAdd){
    Node *newNode = new Node;
    newNode->setData(toAdd);

    if(!head){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
    nodeCount++;
}

void FALR::remove(){
    if(!head){
        cout << "FAFR is empty" << endl;
        return;
    }
    if(tail->getPrev()){
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNext(NULL);
    }
    else{
        delete tail;
        head = NULL;
        tail = NULL;
    }
    nodeCount--;

}

void FALR::setTraverser(){
    if(!traverser)
        traverser = new ARTF;
    traverser->current = head;
}

// LAFR #######################################################################################

LAFR::LAFR(){
    name = "LAFR";
}

LAFR::~LAFR(){
    removeAll();
    delete traverser;
}

void LAFR::add(int toAdd){
    Node *newNode = new Node;
    newNode->setData(toAdd);

    if(!head){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    nodeCount++;
}

void LAFR::remove(){
    if(!head){
        cout << "FAFR is empty" << endl;
        return;
    }

    if(head->getNext()){
        head = head->getNext();
        delete head->getPrev();
        head->setPrev(NULL);
    }
    else{
        delete head;
        head = NULL;
        tail = NULL;
    }
    nodeCount--;
}

void LAFR::setTraverser(){
    if(!traverser)
        traverser = new ARTL;
    traverser->current = tail;
}

// ARTF #######################################################################################

bool ARTF::hasNode(){
    if(current)
        return true;
    else
        return false;
}

int ARTF::next(){
    int toReturn = current->getData();
    current = current->getNext();
    return toReturn;
}

// ARTL #######################################################################################

bool ARTL::hasNode(){
    if(current)
        return true;
    else
        return false;
}

int ARTL::next(){
    int toReturn = current->getData();
    current = current->getPrev();
    return toReturn;
}

















