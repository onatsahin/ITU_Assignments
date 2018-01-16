#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "list.h"

using namespace std;

void List::create(){
  head = NULL;
  tail = NULL;
  personcount = 0;
}

void List::insert_person(char *name){
  Phone_node *traverse , *newnode;
  newnode = new Phone_node;
  strcpy(newnode->name,name);
  traverse = head;
  newnode->next = NULL;
  newnode->prev = NULL;
  if(head == NULL){
    head = newnode;
    tail = newnode;
    personcount++;
    return;
  }
  if( strcmp(newnode->name,head->name) < 0 ){
    newnode->next = head;
    head = newnode;
    (newnode->next)->prev = newnode;
    personcount++;
    return;
  }
  while(traverse && (strcmp(newnode->name,traverse->name) > 0) ){
    traverse = traverse->next;
  }
  if(traverse){
    newnode->next = traverse;
    newnode->prev = (traverse->prev);
    (traverse->prev)->next = newnode;
    traverse->prev = newnode;
  }
  else{
     tail->next = newnode;
     newnode->prev = tail;
     tail = newnode;
  }
  personcount++;
}

void List::insert_number(char *name,char *nnumber, char *type){
  Phone_node *traverse;
  number *newnum;
  number *cur;
  newnum = new number;
  strcpy(newnum->num,nnumber);
  strcpy(newnum->type,type);
  newnum->next = NULL;
  traverse = head;
  while(traverse && (strcmp(name,traverse->name) != 0) ){
    traverse = traverse->next;
  }
  if(traverse){
    cur = traverse->phonenum;
    if(cur == NULL){
      traverse->phonenum = newnum;
      return;
    }
    while(cur->next){
      cur = cur->next;
    }
    cur->next = newnum;
  }
  else{
    cout << "There is not any person that you  recall."<<endl;
    }
}

void List::printall(){
    Phone_node *traverse;
    number *pn;
    traverse = head;
    int i=1;
    while(traverse){
      cout << i << "." << traverse->name;
      pn = traverse->phonenum;
      while(pn){
        cout << "   "<< pn->type << " " << pn->num <<"  ";
        pn = pn->next;
      }
      cout << endl;
      traverse = traverse->next;
      i++;
    }
}


void List::remove_person(int ordernum){
  Phone_node *traverse;
  traverse = head;
  number *pn;
  int counter = 1;
  if(ordernum <= 0 ){
    cout << "The index is too small"<<endl;
    return;
}
  if(ordernum == 1){
    pn = traverse->phonenum;
    while(pn){
      traverse->phonenum = pn->next;
      delete pn;
      pn = traverse->phonenum;
    }
    if( head->next ){
      head = head->next;
      head->prev = NULL;
    }
    else{
    head = NULL;
}
    delete traverse;
    personcount--;
    return;
  }
  while( (traverse != NULL)  && (counter < ordernum) ){
    traverse = traverse->next;
    counter++;
  }
  if(counter < ordernum){
    cout << "This index is too big"<<endl;
  }
  else {
    pn = traverse->phonenum;
    while(pn){
      traverse->phonenum = pn->next;
      delete pn;
      pn = traverse->phonenum;
    }
    (traverse->prev)->next = traverse->next;
    if(traverse->next){
      (traverse->next)->prev = traverse->prev;
}
    else
      tail = traverse->prev;
    delete traverse;
    personcount--;
  }
}
void List::remove_number(int ordernum,char *ttype){
  Phone_node *traverse;
  number *pn,*pp;
  traverse = head;
  int counter = 1;
  if(ordernum <= 0 ){
    cout << "The index is too small"<<endl;
    return;
}
  while( (traverse != NULL)  && (counter < ordernum) ){
    traverse = traverse->next;
    counter++;
  }
  if(counter < ordernum){
    cout << "This index is too big"<<endl;
  }
  else{
    pn = traverse->phonenum;
    pp = traverse->phonenum;
    while(pn){
      if(strcmp(ttype,pn->type)==0){
        if(pn = traverse->phonenum){
          traverse->phonenum = pn->next;
          delete pn;
          return;
        }
        pp->next = pn->next;
        delete pn;
        return;
      }
      pp = pn;
      pn = pn->next;
    }
  }

}
