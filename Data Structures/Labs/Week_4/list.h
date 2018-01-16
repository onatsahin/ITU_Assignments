#ifndef LIST_H
#define LIST_H
#include "node.h"
#include <string>

using namespace std;

struct List{
  Phone_node *head;
  int nodecount;
  void create();
  void close();
  void printList();
  void insert(Phone_node *);
  void remove(int ordernum);
  int search(char* a);
  void update(int recordnum, Phone_node *);
};
#endif
