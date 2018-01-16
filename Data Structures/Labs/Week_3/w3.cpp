#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <string.h>

using namespace std;

struct Person{
  char *name;
  char *number;
  char *surname;
};

Person *people;
Person *temparr;
int personcount=0;
int max_index = 2;

void user_menu();
void add();
void list();
void rec_delete();
void update();
void search();

int main(){
  people = new Person [max_index];
  user_menu();
  delete [] people;
  return 0;
}

void user_menu(){
  bool exit = true;
  char choice,choice2;
  while(exit){
    system("clear");
    cout << "Press A to add"<< endl;
    cout << "Press L to list"<<endl;
    cout << "Press D to delete" << endl;
    cout << "Press U to update" << endl;
    cout << "Press S to search"<<endl;
    cout <<  "Press E to exit"<<endl;
    cin >> choice;
    getchar();
    switch (choice) {

      case 'A': case 'a':
            add();
            break;
      case 'L' : case 'l':
            list();
            getchar();
            break;
      case 'D' : case 'd':
            rec_delete();
            break;
      case 'U': case 'u':
            update();
            break;
      case 'S': case 's':
            search();
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
}

void add(){
  Person temp;
  int i,j;
  int writeIndex = 0;

  temp.name = new char[20];
  temp.number = new char[20];
  temp.surname = new char[20];
  cout << "Enter name of the person"<< endl;
  cin.getline(temp.name,'\n');
  cout << "Enter surname of the person"<< endl;
  cin.getline(temp.surname,'\n');
  cout << "Enter number of the person"<< endl;
  cin.getline(temp.number,'\n');

  if(personcount > max_index - 1){
    temparr = new Person [personcount];
    for (i = 0 ; i < personcount ; i++) {
      temparr[i] = people[i];
    }
    delete [] people;
    people = new Person [max_index*2];
    for (i = 0 ; i < personcount ; i++) {
      people[i] = temparr[i];
    }
    delete [] temparr;
  }
  for(i = 0 ; i < personcount ; i++){
      if( toupper(people[i].name[0]) < toupper(temp.name[0])) writeIndex++;

      if( toupper(people[i].name[0]) == toupper(temp.name[0])){
        for(j = 1 ; j < strlen(people[i].name) ||  j < strlen(temp.name) ;j++){
          if( toupper(people[i].name[j]) < toupper(temp.name[j])) {
            writeIndex++;
            break;}
          if( toupper(people[i].name[j]) == toupper(temp.name[j]))continue;
          if( toupper(people[i].name[j]) > toupper(temp.name[j])) break;
        }
      }
      if( toupper(people[i].name[0]) > toupper(temp.name[0])){
        break;
      }
    }
    people[personcount].name = new char[sizeof(temp.name)];
    people[personcount].number = new char[sizeof(temp.number)];
    people[personcount].surname = new char[sizeof(temp.surname)];

    personcount++;

  for(i = personcount-1 ; i > writeIndex ; i--){
    strcpy(people[i].name,people[i-1].name);
    strcpy(people[i].number,people[i-1].number);
    strcpy(people[i].surname,people[i-1].surname);
}
  strcpy(people[writeIndex].name,temp.name);
  strcpy(people[writeIndex].surname,temp.surname);
  strcpy(people[writeIndex].number,temp.number);

delete [] temp.number;
delete [] temp.name;
delete [] temp.surname;
}

void list(){
  int i;
  for(i=0 ; i < personcount; i++){
    cout <<i+1 << "." <<people[i].name << " " << people[i].surname <<" "<<people[i].number << endl;
   }
}

void rec_delete(){
  int deleteIndex;
  int i=0;

  list();
  cout << "Please enter index of desired person" << endl;
  cin >> deleteIndex;
  personcount--;
  for(i = deleteIndex - 1 ; i  < personcount ; i++){
    strcpy(people[i].name,people[i+1].name);
    strcpy(people[i].number,people[i+1].number);
  }

}
void update(){
  int updateIndex;
  int i=0,j;
  rec_delete();
  getchar();
  add();
}

void search(){
  char *decision;
  int foundRecord=0;
  decision = new char [20];
  cout << "Press enter name to search(Press * to look all records)"<<endl;
  cin.getline(decision, 20);
  if( strcmp(decision,"*")==0 ){
    list();
  }
  else{
    for(int i = 0 ; i < personcount ; i++){
      if(strncmp(people[i].name,decision,strlen(decision))==0){
        cout <<i+1 <<"."<<people[i].name<<" "<<people[i].number << endl;
        foundRecord++;
      }
    }
    cout << "There are "<<foundRecord<<" records found"<<endl;
  }



}
