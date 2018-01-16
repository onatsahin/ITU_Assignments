#include "data.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int Tree::BFS(int find) {
    Que Q;
    int step = 0;
    int found = 0;
    nodeTree *u;
    Q.create();
    Q.enque(root);
    while(!Q.isemptyQue()) {
        u = Q.deque();
        if(u->left != NULL)Q.enque(u->left);
        if(u->right != NULL)Q.enque(u->right);
        cout << u->number << " ";
        step++;
        if(u->number == find) {
            found = 1;
            cout << "Number found! "<<endl;
            break;
        }
    }
    if(found == 0){
        cout << "Could not find "<<endl;
    }
    Q.close();
    return step;
}

int Tree::DFS(int find){
    Stack S;
    S.create();
    int found = 0;
    int step = 0;
    nodeTree *u;
    S.push(root);
    while(!S.isempty()){
        u = S.pop();
        if(u->left != NULL)S.push(u->left);
        if(u->right != NULL)S.push(u->right);
        cout << u->number << " ";
        step++;
        if(u->number == find){
            found = 1;
            cout << "Number found! "<<endl;
            break;
        }
    }
    if(found == 0){
        cout << "Could not find "<<endl;
    }
    S.close();
    return step;
}


void Tree::createTree(int N){
    int *array;
    array = new int[N];
    root = new nodeTree;

    for(int i=0; i<N; i++){
        array[i] = i+1;
    }
    for(int i=0; i<N; i++){
        array[i] = rand() % N + 1;
    }
    root->number = array[0];
    root->child = 1;

    for(int i=1; i<N; i++)
        add(root,array[i]);

    delete[] array;
}

void Tree::add(nodeTree *p, int k){
    if( !p->left ){

        p->left=new nodeTree;
        p->left->number=k;
        p->left->child=1;

        p->left->left=NULL;
        p->left->right=NULL;
    }
        else if( !p->right ){

            p->right=new nodeTree;
            p->right->number=k;
            p->right->child=1;

            p->right->left=NULL;
            p->right->right=NULL;
        }
        else if( p->left->child==p->right->child )
            add(p->left,k);
        else
            add(p->right,k);

    if( p->left && p->right ){
        p->child = 1 + p->left->child + p->right->child;
    }
    else if( p->left && !p->right ){
        p->child = 1 + p->left->child;
    }
}

void Tree::InorderSearch(nodeTree *p,int tofind){
    static int step = 0;

    if( p->left )
        InorderSearch(p->left,tofind);

    cout << p->number << " ";
    step++;
    if(tofind == p->number){
        cout << endl <<"Inorder found in " << step <<" steps"<<endl;
        Inorderfound =1;
        return;
    }
    if( p->right )
        InorderSearch(p->right,tofind);
}


void Tree::removeTree(nodeTree *p){
    if(p) {
        if(p->left != NULL){
            removeTree(p->left);
            p->left = NULL;
        }
        if(p->right != NULL){
            removeTree(p->right);
            p->right = NULL;
        }
        delete p;
    }
}

void Stack::create(){
    headStack = NULL;
}

bool Stack::isempty(){
    return headStack == NULL;
}

void Stack::close(){
    node *traverse = headStack;
    while(headStack){
        traverse = headStack;
        headStack = headStack->next;
        delete traverse;
    }
}

void Stack::push(nodeTree* topush){
    node *newnode = new node;
    newnode->data = topush;
    newnode->next = headStack;
    headStack = newnode;
}

nodeTree* Stack::pop(){
    node *temp;
    nodeTree *toreturn = new nodeTree;
    temp = headStack;
    toreturn = temp->data;
    headStack = headStack->next;
    delete temp;
    return toreturn;
}

void Que::create(){
    headQue = NULL;
}
bool Que::isemptyQue(){
    return headQue == NULL;
}
void Que::close(){
    node *traverse;
    while(headQue){
        traverse = headQue;
        headQue = headQue->next;
        delete traverse;
    }
}

void Que::enque(nodeTree* toenque){
    node *newnode = new node;
    newnode->data = toenque;
    newnode->next = NULL;
    if(isemptyQue()){
        backQue = newnode;
        headQue = newnode;
    }
    else{
        backQue->next = newnode;
        backQue = newnode;
    }
}

nodeTree *Que::deque(){
    nodeTree *toreturn = new nodeTree;
    node *traverse = headQue;
    toreturn = headQue->data;
    headQue = headQue->next;
    delete traverse;
    return toreturn;
}
