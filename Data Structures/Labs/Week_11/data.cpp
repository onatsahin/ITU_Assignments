#include <cstring>
#include <iostream>
#include "data.h"
#include <cstdlib>

using namespace std;
void Tree::create(){
    root = NULL;
}
void Tree::close(PhoneNode *p){
    if(p){
        Node *traverse;
        while(p->phonenum){
            traverse = p->phonenum;
            p->phonenum = p->phonenum->next;
            delete [] traverse->num;
            delete traverse;
        }
        if(p->left){
            close(p->left);
            p->left = NULL;
        }
        if(p->right){
            close(p->right);
            p->right = NULL;
        }
        delete [] p->name;
        delete p;
    }
}

void Tree::add(char *toadd){
    PhoneNode *newnode = new PhoneNode;
    PhoneNode *traverse = root;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->phonenum = NULL;
    newnode->name = new char[20];
    strcpy(newnode->name,toadd);
    bool added = false;
    int comparison;

    if(root == NULL){
        root = newnode;
        char addthisnumber[10];
        cout << "Enter the number"<<endl;
        cin.getline(addthisnumber,10);
        addNumber(toadd,addthisnumber);
        return;
    }
    while( (traverse != NULL) && (!added) ){
        comparison = strcmp(newnode->name,traverse->name);
        if(comparison < 0){

            if(traverse->left){
                traverse= traverse->left;
            }
            else{
                traverse->left = newnode;
                added = true;
            }
        }
        else if(comparison > 0){

            if(traverse->right){
                traverse= traverse->right;
            }
            else{
                traverse->right = newnode;
                added = true;
            }
        }
        else{
            char addednumber[10];
            cout << "This person exist enter the number"<<endl;
            cin.getline(addednumber,10);
            addNumber(toadd,addednumber);
            return;
        }
    }
    char addthisnumber[10];
    cout << "Enter the number"<<endl;
    cin.getline(addthisnumber,10);
    addNumber(toadd,addthisnumber);
}

void Tree::addNumber(char *name, char *number){
    PhoneNode *traverse;
    Node *trav;
    Node *newnode = new Node;
    newnode->num = new char[20];
    strcpy(newnode->num,number);
    newnode->next = NULL;
    traverse = search(name);
    if(!traverse->phonenum ){
        traverse->phonenum = newnode;
        return;
    }
    trav = traverse->phonenum;
    while(trav->next)
        trav = trav->next;

    trav->next = newnode;
}

PhoneNode* Tree::search(char *tosearch){
    PhoneNode *traverse = root;
    int comparison;
    while(traverse){
        comparison = strcmp(tosearch,traverse->name);
        if(comparison < 0){
            traverse = traverse->left;
        }
        else if(comparison > 0){
            traverse = traverse->right;
        }
        else{
            break;
        }
    }
    return traverse;
}

void Tree::update(char *oldName, char *newName){
    PhoneNode *newnode = new PhoneNode;
    PhoneNode *traverse = root;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->phonenum = NULL;
    newnode->name = new char[20];
    strcpy(newnode->name,newName);
    bool added = false;
    int comparison;
    if(root == NULL){
        root = newnode;
        return;
    }
    while( (traverse != NULL) && (!added) ){
        comparison = strcmp(newnode->name,traverse->name);
        if(comparison < 0){

            if(traverse->left){
                traverse= traverse->left;
            }
            else{
                traverse->left = newnode;
                added = true;
            }
        }
        else if(comparison > 0){

            if(traverse->right){
                traverse= traverse->right;
            }
            else{
                traverse->right = newnode;
                added = true;
            }
        }
    }
    Node *p;
    traverse = search(oldName);

    while(traverse->phonenum){
        Node *newnum = new Node;
        p = newnode->phonenum;
        newnum->next  = NULL;
        newnum->num = new char[20];
        strcpy(newnum->num,traverse->phonenum->num);
        traverse->phonenum = traverse->phonenum->next;
        if(newnode->phonenum == NULL){
            newnode->phonenum = newnum;
        }
        else{
            while(p->next)
                p = p->next;
            p->next = newnum;
        }
    }
    deletePerson(oldName);
}

void Tree::deleteNum(char *todelete){
    PhoneNode *traverse;
    Node *trav;
    Node *tail;
    int index =0;
    traverse = search(todelete);
    if(!traverse)
        cout << "This person does not exist."<<endl;

    else {
        trav = traverse->phonenum;
        while(trav){
            index++;
            cout <<index<< ". "<< trav->num <<endl;
            trav = trav->next;
        }
        index = 0;
        tail = traverse->phonenum;
        trav = traverse->phonenum;
        cout << "Which number do you like to delete"<<endl;
        cin >> index;
        index--;
        cin.ignore(1000,'\n');
        if(index == 0){
            traverse->phonenum = traverse->phonenum->next;
            delete [] tail->num;
            delete tail;
            return;
        }
        while(index--){
            tail = trav;
            trav = trav->next;
        }
        tail->next = trav->next;
        delete [] trav->num;
        delete trav;
    }
}
void Tree::deletePerson(char *todelete){
    PhoneNode *traverse,*parent;
    traverse = root;
    bool found = false;
    int comparison;
    char direc = 'k';
    while(traverse && !found){
        comparison = strcmp(todelete,traverse->name);

        if(comparison < 0 ){
            parent = traverse;
            traverse = traverse->left;
            direc = 'l';
        }
        else if (comparison > 0){
            parent = traverse;
            traverse = traverse->right;
            direc = 'r';
        }
        else {
            found = true;
        }
    }
    if(found){
        if(traverse->left == NULL && traverse->right == NULL){

            if(direc == 'l')
                parent->left= NULL;
            else if(direc == 'r')
                parent->right = NULL;
            else
                root = NULL;
        }
        else if(traverse->left == NULL){
            if(direc == 'l')
                parent->left = traverse->right;
            else if(direc == 'r')
                parent->right = traverse->right;
            else
                root = traverse->right;
        }
        else if(traverse->right == NULL){
            if(direc == 'l')
                parent->left = traverse->left;
            else if(direc == 'r')
                parent->right = traverse->left;
            else
                root = traverse->left;
        }
        else{
            PhoneNode *q = traverse->right;
            while(q->left)
                q = q->left;
            q->left = traverse->left;
            if(direc == 'l')
                parent->left = traverse->right;
            else if(direc == 'r')
                parent->right = traverse->right;
            else
                root = traverse->right;
        }
        Node *tr= traverse->phonenum;
        while(tr){
            traverse->phonenum = traverse->phonenum->next;
            delete [] tr->num;
            tr->next = NULL;
            delete tr;
            tr = traverse->phonenum;
        }
        traverse->left = NULL;
        traverse->right = NULL;
        delete [] traverse->name;
        delete traverse;
    }
    else {
        cout << "Could not find person"<<endl;
    }
}

void Tree::PrintAll(PhoneNode *p){

    if(p){
        int i=1;
        Node *trav = p->phonenum;
        PrintAll(p->left);
        cout << p->name << endl;
        while(trav){
            cout <<"\t" << i << ". "<< trav->num<<endl;
            i++;
            trav = trav->next;
        }
        PrintAll(p->right);
    }
}
