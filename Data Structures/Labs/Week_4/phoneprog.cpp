#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "list.h"

using namespace std;

typedef Phone_node Phone_record;
typedef List Datastructure;
Datastructure book;


void search_record();
void remove_record();
void add_record();
void printAll();
void uptade_record();

int main(){
  book.create();
  bool exit = true;
  char choice,choice2;
  while(exit){
    system("clear");
    cout << "Press A to add"<< endl;
    cout << "Press L to list"<<endl;
    cout << "Press R to delete" << endl;
    cout << "Press U to update" << endl;
    cout << "Press S to search"<<endl;
    cout <<  "Press E to exit"<<endl;
    cin >> choice;
    getchar();
    switch (choice) {

      case 'A': case 'a':
            add_record();
            getchar();
            break;
      case 'U': case 'u':
          uptade_record();
            break;
      case 'L':case 'l':
            printAll();
            getchar();
            break;
      case 'R':case 'r':
            remove_record();
            getchar();
            break;
      case 'S': case 's':
            search_record();
            getchar();
            getchar();
            break;
      case 'E': case 'e':
        cout<< "Sure want to quit?(Press Y to exit or N to continue)"<< endl;
        cin >> choice2;
        if(choice2 == 'Y' || choice2 == 'y')exit = false;
        break;
      default:
        cout << "Enter a valid character.Enter one of these {A,L,D,U,S,E} " << endl;
        cin >> choice;
        getchar();
      }
}
  book.close();
return 0;
}

void search_record(){
  cout << "Please Enter a name to search:";
  char *name;
  name = new char[20];
  cin >> name;
  cout << book.search(name) << " records found"<<endl;
}

void add_record(){
  Phone_record k;
  cout << "Enter the name of new person:";
  cin.getline(k.name,20);
  cout << "Enter the number of new person:";
  cin.getline(k.phonenum,20);
  book.insert(&k);
  cout << "Record addded"<<endl;
}
void printAll(){
  book.printList();
}
void remove_record(){
  book.printList();
  cout << "Enter index:";
  int index;
  cin >> index;
  book.remove(index);

}
void uptade_record(){
  remove_record();
  getchar();
  add_record();
}
