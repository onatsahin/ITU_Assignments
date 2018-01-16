#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "struct.h"

using namespace std;

void print_menu();

int main(){
    char choice;
    list player;
    player.create();

    while(choice != 'E' && choice != 'e'){
        system("clear");
        print_menu();
        cout << "Enter a choice (P,L,A,R,C,D,W,E): ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if(choice == 'A' || choice == 'a')
            player.addSong();

        else if(choice == 'R' || choice == 'r')
            player.removeSong();

        else if(choice == 'C' || choice == 'c')
            player.createList();

        else if(choice == 'D' || choice == 'd')
            player.deleteList();

        else if(choice == 'W' || choice == 'w')
            player.writeToFile();

        else if(choice == 'P' || choice == 'p')
            player.play();

        else if(choice == 'L' || choice == 'l')
            player.printList();

        //if(choice == 'E' || choice == 'e') break;

    }

    player.Exit();

    return 0;
}

void print_menu(){
    cout << "SONG BOX APPLICATION (USING DOUBLY, CIRCULAR MULTI LINKED LIST)" << endl;
    cout << "Choose an operation" << endl;
    cout << "P: Play" << endl;
    cout << "L: Show all playlists" << endl;
    cout << "A: Add songs to a playlist" << endl;
    cout << "R: Remove songs from a playlist" << endl;
    cout << "C: Create a new playlist" << endl;
    cout << "D: Delete a playlist" << endl;
    cout << "W: Write to file (SAVE)" << endl;
    cout << "E: Exit" << endl;
}
