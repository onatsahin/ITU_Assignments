#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "data.h"


using namespace std;

int main()
{
    Tree bst;
    bst.create();
    bool exit = false;
    int index;
    char *name;
    char number[20];
    while(!exit){
        name = new char[20];
        system("clear");
        cout << "1.Add Person" <<endl<< "2.Update" <<endl<< "3.Delete Number\n" << "4.Delete Person\n"<< "5.Print\n"<<"6.Exit" <<endl;
        cout << "Enter index: "<<endl;
        cin >> index;
        cin.ignore(1000,'\n');
        if(index == 1){
            cout << "Enter the name"<<endl;
            cin.getline(name,20);
            bst.add(name);
        }
        else if(index == -1){
            cout << "Enter the name"<<endl;
            cin.getline(name,20);
            cout << "Enter the number"<<endl;
            cin.getline(number,20);
            bst.addNumber(name,number);
        }
        else if(index == 2){
            cout << "Enter the name"<<endl;
            cin.getline(name,20);
            cout << "Enter the new name"<<endl;
            cin.getline(number,20);
            bst.update(name,number);
        }
        else if(index == 3){
            cout << "Enter the name"<<endl;
            cin.getline(name,20);
            bst.deleteNum(name);
        }
        else if(index == 4){
            cout << "Enter the name"<<endl;
            cin.getline(name,20);
            bst.deletePerson(name);
        }
        else if(index == 5){
            bst.PrintAll(bst.root);
        }
        else if(index == 6){
            exit = true;
            break;
        }
        getchar();
    }
    bst.close(bst.root);
        return 0;
}
