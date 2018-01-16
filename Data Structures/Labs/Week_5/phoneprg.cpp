#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "list.h"

using namespace std;


typedef Phone_node Phone_record;
typedef number NUMBER;
typedef List Datastructure;
Datastructure book;

void addPerson();
void addNumber();
void Listall();
void deleteperson();
void deletenumber();

int main(){
  book.create();
  bool exit = true;
  char choice,choice2;
  while(exit){
    system("clear");
    cout << "Press A to add a person"<< endl;
    cout << "Press N to add number for a person"<<endl;
    cout << "Press L to list"<<endl;
    cout << "Press R to delete a person" << endl;
    cout << "Press D to delete a number" << endl;
    cout << "Press U to update" << endl;
    cout << "Press S to search"<<endl;
    cout <<  "Press E to exit"<<endl;
    cin >> choice;
    getchar();
    switch (choice) {
      case 'A': case 'a':
            addPerson();
            getchar();
            break;
      case 'N': case 'n':
            addNumber();
            getchar();
            break;
      case 'U': case 'u':
            break;
      case 'L':case 'l':
            Listall();
            getchar();
            break;
      case 'R':case 'r':
            deleteperson();
            getchar();
            break;
      case 'D':case 'd':
            deletenumber();
            getchar();
            break;
      case 'S': case 's':
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

return 0;
}
void Listall(){
  book.printall();
}
void addPerson(){
  cout << "Please enter name of the person"<<endl;
  char newname[20];
  cin.getline(newname,20);
  book.insert_person(newname);
  cout << "Person added"<<endl;
}
void addNumber(){
  char newname[20],types[20],znumber[20];
  cout << "Please enter name of the person you want to add him number"<<endl;
  cin.getline(newname,20);
  cout << "Please enter first type than number of it"<<endl;
  cin.getline(types,20);
  cin.getline(znumber,20);
  book.insert_number(newname,znumber,types);
  cout << "Number added"<<endl;
}
void deleteperson(){
  int index;
  book.printall();
  cout << "Please enter index of desired person"<<endl;
  cin >> index;
  book.remove_person(index);
  cout << "You deleted a record"<<endl;
}
void deletenumber(){
  char newtype[20];
  int index;
  cout << "Please enter index and type of desired number"<<endl;
  cin.getline(newtype,20);
  cin >> index;
  book.remove_number(index,newtype);
  cout << "You deleted a number"<<endl;
}
