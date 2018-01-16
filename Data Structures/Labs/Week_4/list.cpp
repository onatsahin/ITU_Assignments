#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "list.h"

using namespace std;

void List::create(){
  head = NULL;
  nodecount = 0;
}

int List::search(char *a){
    Phone_node *traverse;
    int counter = 0;
    int found = 0;
    traverse = head;
    while(traverse){
      counter++;
      if( strncmp(traverse->name,a,strlen(a)) == 0 ){
        found++;
        cout << counter << "." << traverse->name << " " << traverse->phonenum << endl;
      }
      traverse = traverse->next;
    }
    return found;
}

void List::insert(Phone_node *k){
  Phone_node *traverse , *tail;
  Phone_node *new_node;
  new_node = new Phone_node;
  *new_node = *k;
  new_node->next = NULL;
  traverse = head;
  if(head == NULL){
    head = new_node;
    nodecount++;
    return;
  }
  if( strcmp(new_node->name,head->name) < 0 ){
    new_node->next = head;
    head = new_node;
    nodecount++;
    return;
  }
  while(traverse && (strcmp(new_node->name,head->name) > 0) ){
    tail = traverse;
    traverse = traverse->next;
  }
  if(traverse){
    new_node->next = traverse;
    tail->next = new_node;
  }
  else{
    tail->next = new_node;
  }
  nodecount++;

}
void List::printList(){
  Phone_node *traverse;
  traverse = head;
  int i = 0;
  while(traverse){
    i++;
    cout << i << "." << traverse->name << " " << traverse->phonenum << endl;
    traverse = traverse->next;
  }

}
void List::remove(int ordernum){
  Phone_node *traverse , *tail;
  int i=0;
  int index = 1;
  traverse = head;

  if(ordernum == 1){
    head = head->next;
    delete traverse;
    nodecount--;
    return;
  }
  while((traverse != NULL) && (index < ordernum) ){
    tail = traverse;
    traverse = traverse->next;
    index++;
  }
  if(index < ordernum){
    cout << "Wrong index"<<endl;
    return;
  }
  else{
    tail->next = traverse->next;
    delete traverse;
    nodecount--;
  }
}
void List::close(){
  Phone_node *p;
  while(p){
    p = head;
    head = head->next;
    delete p;
  }


}
