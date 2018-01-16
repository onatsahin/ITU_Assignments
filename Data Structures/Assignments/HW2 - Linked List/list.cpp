#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "struct.h"

using namespace std;

void list::create(){
    playlist_count = 3;
    char checker;
    int randomnumber;
    song_node *toadd;
    playlist *userlist;
    srand(time(NULL));

    if(!(database = fopen("songbook.txt", "r+"))){//Opening the file
        cerr << "File can not be opened" << endl;
        exit(1);
    }
    head = new playlist;//initialize new playlist
    head->songnumber = 0;
    head->name = new char[LNAME_LENGTH];
    strcpy(head->name, "CHRONOLOGICAL");
    head->next = head;
    head->prev = head;

    head->head = new song_node;//initialize head of the playlist
    head->head->next = head->head;
    head->head->prev = head->head;
    head->head->parent = head;

    head->head->data = new song;//initialize the data of the head
    head->head->data->name = new char[SNAME_LENGTH];
    head->head->data->singer = new char[SINGER_LENGTH];
    head->head->data->style = new char[STYLE_LENGTH];
    fseek(database, 0, SEEK_SET);

    fscanf(database, "%[^\t]s", head->head->data->name);
    fseek(database, 1, SEEK_CUR);

    fscanf(database, "%[^\t]s", head->head->data->singer);
    fseek(database, 1, SEEK_CUR);

    fscanf(database, "%d", &(head->head->data->year));
    fseek(database, 1, SEEK_CUR);

    fscanf(database, "%[^\r]s", head->head->data->style);
    fseek(database, 2, SEEK_CUR);

    head->songnumber++;

    //checker = '\n';
    //cout << head->head->data->name << head->head->data->singer << head->head->data->year << head->head->data->style << endl;
    while(/*!feof(database)*/ /*checker == '\n'*/1){
        toadd = new song_node;
        toadd->parent = head;
        toadd->data = new song;
        toadd->data->name = new char[SNAME_LENGTH];
        toadd->data->singer = new char[SINGER_LENGTH];
        toadd->data->style = new char[STYLE_LENGTH];

        fscanf(database, "%[^\t]s", toadd->data->name);
        fseek(database, 1, SEEK_CUR);

        fscanf(database, "%[^\t]s", toadd->data->singer);
        fseek(database, 1, SEEK_CUR);

        fscanf(database, "%d", &(toadd->data->year));
        fseek(database, 1, SEEK_CUR);

        fscanf(database, "%[^\r]s", toadd->data->style);
        //cout << toadd->data->name << toadd->data->singer << toadd->data->year << toadd->data->style << endl;

        head->head->prev->next = toadd;
        toadd->prev = head->head->prev;
        head->head->prev = toadd;
        toadd->next = head->head;

        head->songnumber++;

        //fseek(database, 1, SEEK_CUR);//skipping \r and \n

        if(feof(database)) break;
        fseek(database, 2, SEEK_CUR);

        checker = fgetc(database);
        if(checker == '*'){
            fseek(database, -1, SEEK_CUR);
            break;
        }
        else{
            fseek(database, -1, SEEK_CUR);
        }


        /*checker = fgetc(database);
        if(checker == '*'){
            fseek(database, -1, SEEK_CUR);
            break;
        }

        fseek(database, -1, SEEK_CUR);
        //if(checker != '\n') break;*/
    }
    /*cout << head->name << " " << head->songnumber << endl;
    cout << head->head->data->name << head->head->data->singer << head->head->data->year << head->head->data->style << endl;
    song_node *trav = head->head->next;
    while(trav != head->head){
        cout << trav->data->name << trav->data->singer << trav->data->year << trav->data->style << endl;
        trav = trav->next;
    }*/
    playlist *sorted = new playlist;
    sorted->songnumber = 0;
    sorted->name = new char[LNAME_LENGTH];
    strcpy(sorted->name, "SORTED");
    head->next = sorted;
    head->prev = sorted;
    sorted->next = head;
    sorted->prev = head;
    sorted->head = new song_node;

    sorted->head->parent = sorted;
    sorted->head->data = head->head->data;
    sorted->head->next = sorted->head;
    sorted->head->prev = sorted->head;
    sorted->songnumber++;

    song_node *travhead = head->head->next;

    song_node *trav;

    while(travhead != head->head){
        toadd = new song_node;
        toadd->parent = sorted;
        toadd->data = travhead->data;
        if(strcmp(toadd->data->singer, sorted->head->data->singer) < 0){
            sorted->head->prev->next = toadd;
            toadd->prev = sorted->head->prev;
            toadd->next = sorted->head;
            sorted->head->prev = toadd;
            sorted->head = toadd;
        }
        else if(strcmp(toadd->data->singer, sorted->head->data->singer) == 0){
            trav = sorted->head;
            int added = 0;
            while(strcmp(toadd->data->singer, trav->data->singer) == 0 && trav != sorted->head){
                if(strcmp(toadd->data->name, trav->data->name) < 0){
                    trav->prev->next = toadd;
                    toadd->prev = trav->prev;
                    toadd->next = trav;
                    trav->prev = toadd;
                    if(trav == sorted->head){
                        sorted->head = toadd;
                    }
                    added = 1;
                }
                else{
                    trav = trav->next;
                }
            }
            if(added == 0){
                trav->prev->next = toadd;
                toadd->prev = trav->prev;
                toadd->next = trav;
                trav->prev = toadd;
                if(trav == sorted->head){
                    sorted->head = toadd;
                }
            }
        }
        else if(strcmp(toadd->data->singer, sorted->head->data->singer) > 0){
            int added = 0;
            trav = sorted->head->next;
            while(strcmp(toadd->data->singer, trav->data->singer) > 0 && trav != sorted->head){
                trav = trav->next;
            }
            if(strcmp(toadd->data->singer, trav->data->singer) == 0){
                while(strcmp(toadd->data->singer, trav->data->singer) == 0){
                    if(strcmp(toadd->data->name, trav->data->name) < 0){
                        trav->prev->next = toadd;
                        toadd->prev = trav->prev;
                        toadd->next = trav;
                        trav->prev = toadd;
                        /*if(trav == sorted->head){
                            sorted->head = toadd;
                        }*/
                        added = 1;
                        break;
                    }
                    else{
                        trav = trav->next;
                    }
                }
            }
            else if(strcmp(toadd->data->singer, trav->data->singer) < 0){
                trav->prev->next = toadd;
                toadd->prev = trav->prev;
                toadd->next = trav;
                trav->prev = toadd;
                if(trav == sorted->head){
                    sorted->head = toadd;
                }
                added = 1;
            }
            if(added == 0){
                trav->prev->next = toadd;
                toadd->prev = trav->prev;
                toadd->next = trav;
                trav->prev = toadd;
                /*if(trav == sorted->head){
                    sorted->head = toadd;
                }*/
            }
        }
        sorted->songnumber++;
        travhead = travhead->next;

        }
        /*cout << sorted->name << " " << sorted->songnumber << endl;
        cout << sorted->head->data->singer << "   "<< sorted->head->data->name << " " << sorted->head->data->year << "  "<< sorted->head->data->style << endl;
        trav = sorted->head->next;
        while(trav != sorted->head){
            cout << trav->data->singer << "   " << trav->data->name << "  " << trav->data->year << "   " << trav->data->style << endl;
            trav = trav->next;
        }*/

    playlist *random = new playlist;
    random->songnumber = 0;
    random->name = new char[LNAME_LENGTH];
    strcpy(random->name, "RANDOM");
    sorted->next = random;
    random->prev = sorted;
    head->prev = random;
    random->next = head;
    random->head = new song_node;
    random->head->parent = random;
    random->head->next = random->head;
    random->head->prev = random->head;

    randomnumber = rand() % head->songnumber-1;
    travhead = head->head;
    for(int i=0; i<randomnumber; i++){
        travhead = travhead->next;
    }
    random->head->data = travhead->data;
    random->songnumber++;
    int check;
    for(int i=0; i<head->songnumber-2; i++){
        check = 0;
        toadd = new song_node;
        toadd->parent = random;
        while(check == 0){
            check = 1;
            travhead = head->head;
            randomnumber = rand() % head->songnumber-1;
            for(int j=0; j<randomnumber; j++){
                travhead = travhead->next;
            }
            toadd->data = travhead->data;
            trav = random->head;

            if(trav->data == toadd->data){
                check = 0;
                continue;
            }
            trav = trav->next;
            while(trav != random->head){
                if(trav->data == toadd->data){
                    check = 0;
                    break;
                }
                else trav = trav->next;
            }

        }
        random->head->prev->next = toadd;
        toadd->prev = random->head->prev;
        random->head->prev = toadd;
        toadd->next = random->head;
        random->songnumber++;

    }
    travhead = head->head;
    check = 1;
    do{
        check = 1;
        trav = random->head;

        do{
            if(travhead->data == trav->data){
                check = 0;
                break;
            }
            trav = trav->next;
        }while(trav != random->head);

        if(check == 1) break;
        travhead = travhead->next;
    }while(travhead != head->head);

    toadd = new song_node;
    toadd->parent = random;
    toadd->data = travhead->data;
    random->head->prev->next = toadd;
    toadd->prev = random->head->prev;
    random->head->prev = toadd;
    toadd->next = random->head;
    random->songnumber++;

    /*cout << random->name << " " << random->songnumber << endl;
    cout << random->head->data->singer << "   "<< random->head->data->name << " " << random->head->data->year << "  "<< random->head->data->style << endl;
    trav = random->head->next;
    while(trav != random->head){
        cout << trav->data->singer << "   " << trav->data->name << "  " << trav->data->year << "   " << trav->data->style << endl;
        trav = trav->next;
    }*/
    /*playlist *temp = head;
    do{
        cout << temp->name;
        cout << temp->head->data->name << endl;
        temp = temp->next;
    }while(temp != head);*/
    checker = fgetc(database);
    fseek(database, -1, SEEK_CUR);
    char *temp = new char[50];
    while(checker == '*'){

        fseek(database, 7, SEEK_CUR);
        userlist = new playlist;
        userlist->head = NULL;
        userlist->songnumber = 0;

        head->prev->next = userlist;
        userlist->prev = head->prev;
        head->prev = userlist;
        userlist->next = head;

        userlist->name = new char[LNAME_LENGTH];

        fscanf(database, "%[^\r]s", userlist->name);
        fseek(database, 2, SEEK_CUR);

        do{
            //cout << "sdgf" << endl;
            travhead = head->head;
            toadd = new song_node;
            toadd->parent = userlist;
            fscanf(database, "%[^\t]s", temp); //reading the name of the song
            if(strcmp(temp, "") == 0) break;

            do{
                if(strcmp(travhead->data->name, temp)==0){
                    toadd->data = travhead->data;
                    break;
                }
                travhead = travhead->next;
            }while(travhead != head->head);

            fscanf(database, "%[^\t]s", temp);//skipping other info about the song
            fscanf(database, "%[^\t]s", temp);
            fscanf(database, "%[^\r]s", temp);
            fseek(database, 2, SEEK_CUR);

            if(userlist->head == NULL){
                userlist->head = toadd;
                toadd->next = toadd;
                toadd->prev = toadd;
            }
            else{
                userlist->head->prev->next = toadd;
                toadd->prev = userlist->head->prev;
                userlist->head->prev = toadd;
                toadd->next = userlist->head;
            }
            userlist->songnumber++;
            //cout << userlist->name << toadd->data->name << endl;
            /*if(feof(database)){
                cout << "feof" << endl;
                break;
            }*/
            checker = fgetc(database);
            fseek(database, -1, SEEK_CUR);
        }while((checker >= 65 && checker <= 90) || (checker >= 97 && checker <= 122));//checks if the checker is a letter
        playlist_count++;
    }
    fclose(database);
}

void list::createList(){
    int choice, index = 0, counter;
    playlist *sorted = head->next;
    playlist *travlist = head;
    song_node *trav, *toadd;

    playlist *newplaylist = new playlist;
    newplaylist->head = NULL;
    newplaylist->songnumber = 0;
    head->prev->next = newplaylist;
    newplaylist->prev = head->prev;
    head->prev = newplaylist;
    newplaylist->next = head;

    system("clear");
    cout << "1. Songs of a specific style" << endl;
    cout << "2. Songs of a specific singer" << endl;
    cout << "3. Combination of existing playlists" << endl;
    cout << "4. Combination of existing songs" << endl;
    cout << "Choose an option: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if(choice == 1){
        char *style = new char[STYLE_LENGTH];
        cout << "Enter a style (Please enter in capital letters): ";
        cin.getline(style, STYLE_LENGTH);
        trav = sorted->head;

        do{
            if(strcmp(trav->data->style, style) == 0){

                toadd = new song_node;
                toadd->parent = newplaylist;
                toadd->data = trav->data;

                if(newplaylist->head == NULL){
                    newplaylist->head = toadd;
                    toadd->next = toadd;
                    toadd->prev = toadd;
                }
                else{
                    newplaylist->head->prev->next = toadd;
                    toadd->prev = newplaylist->head->prev;
                    newplaylist->head->prev = toadd;
                    toadd->next = newplaylist->head;
                }
                newplaylist->songnumber++;
            }
            trav = trav->next;
        }while(trav != sorted->head);

        if(newplaylist->songnumber == 0)
            cout << "Style not found" << endl;

        delete[] style;
    }

    if(choice == 2){
        char *singer = new char[SINGER_LENGTH];
        cout << "Enter an artist (Please enter in capital letters): ";
        cin.getline(singer, SINGER_LENGTH);
        trav = sorted->head;

        do{
            if(strcmp(trav->data->singer, singer) == 0){

                toadd = new song_node;
                toadd->parent = newplaylist;
                toadd->data = trav->data;

                if(newplaylist->head == NULL){
                    newplaylist->head = toadd;
                    toadd->next = toadd;
                    toadd->prev = toadd;
                }
                else{
                    newplaylist->head->prev->next = toadd;
                    toadd->prev = newplaylist->head->prev;
                    newplaylist->head->prev = toadd;
                    toadd->next = newplaylist->head;
                }
                newplaylist->songnumber++;
            }
            trav = trav->next;
        }while(trav != sorted->head);

        if(newplaylist->songnumber == 0)
            cout << "Style not found" << endl;

        delete[] singer;
    }

    if(choice == 3){
        while(1){
            travlist = head;
            counter = 1;
            system("clear");
            for(int i=0; i<playlist_count; i++){
                cout << counter << ". " << travlist->name << endl;
                counter++;
                travlist = travlist->next;
            }
            cout << "Enter an index to combine. Enter -1 to stop combining: " <<endl;
            cin >> index;
            cin.ignore(1000, '\n');

            if(index == -1) break;

            travlist = head;
            for(int i=1; i<index; i++){
                travlist = travlist->next;
            }
            trav = travlist->head;

            do{
                toadd = new song_node;
                toadd->parent = newplaylist;
                toadd->data = trav->data;

                if(newplaylist->head == NULL){
                    newplaylist->head = toadd;
                    toadd->next = toadd;
                    toadd->prev = toadd;
                }
                else{
                    newplaylist->head->prev->next = toadd;
                    toadd->prev = newplaylist->head->prev;
                    newplaylist->head->prev = toadd;
                    toadd->next = newplaylist->head;
                }
                newplaylist->songnumber++;
                trav = trav->next;
            }while(trav != travlist->head);

        }
    }

    if(choice == 4){
        while(1){
            trav = sorted->head;
            counter = 1;
            system("clear");
            do{
                cout << counter << ". " << trav->data->name << "\t" << trav->data->singer << "\t" << trav->data->year << "\t" << trav->data->style << endl;
                counter++;
                trav = trav->next;
            }while(trav != sorted->head);

            cout << "Enter an index to combine. Enter -1 to stop combining: " <<endl;
            cin >> index;
            cin.ignore(1000, '\n');

            if(index == -1) break;

            trav = sorted->head;
            for(int i=1; i<index; i++){
                trav = trav->next;
            }
            toadd = new song_node;
            toadd->parent = newplaylist;
            toadd->data = trav->data;

            if(newplaylist->head == NULL){
                newplaylist->head = toadd;
                toadd->next = toadd;
                toadd->prev = toadd;
            }
            else{
                newplaylist->head->prev->next = toadd;
                toadd->prev = newplaylist->head->prev;
                newplaylist->head->prev = toadd;
                toadd->next = newplaylist->head;
            }
            cout << newplaylist->head->prev->data->name << endl;
            newplaylist->songnumber++;

        }
    }


    newplaylist->name = new char[LNAME_LENGTH];
    cout << "Enter a name for the playlist: ";
    cin.getline(newplaylist->name, LNAME_LENGTH);
    playlist_count++;

    /*cout << head->prev->name << " " << head->prev->songnumber << endl;
    cout << head->prev->head->data->singer << "   "<< head->prev->head->data->name << " " << head->prev->head->data->year << "  "<< head->prev->head->data->style << endl;
    trav = head->prev->head->next;
    while(trav != head->prev->head){
        cout << trav->data->singer << "   " << trav->data->name << "  " << trav->data->year << "   " << trav->data->style << endl;
        trav = trav->next;
    }*/
    cout << "Playlist created." << endl;
    getchar();
}

void list::addSong(){
    int choice;
    playlist *travlist = head->next->next->next;
    song_node *trav = head->next->head;
    song_node *toadd;
    int counter = 1;

    if(travlist == head){
        cout << "There is no user-generated playlist" << endl;
        getchar();
        return;
    }
    system("clear");
    while(travlist != head){
        cout << counter << ". " << travlist->name << endl;
        counter++;
        travlist = travlist->next;
    }
    cout << "Enter index of the playlist you want to add a song: ";
    cin >> choice;
    cin.ignore(1000, '\n');
    travlist = head->next->next->next;

    for(int i=1; i<choice; i++){
        travlist = travlist->next;
    }
    counter = 1;
    do{
        cout << counter << ". " << trav->data->name << "\t" << trav->data->singer << "\t" << trav->data->year << "\t" << trav->data->style << endl;
        trav = trav->next;
        counter++;
    }while(trav != head->next->head);
    cout << "Enter index of the song you want to add: ";
    cin >> choice;
    cin.ignore(1000, '\n');
    trav = head->next->head;
    for(int i=1; i<choice; i++){
        trav = trav->next;
    }

    toadd = new song_node;
    toadd->parent = travlist;
    toadd->data = trav->data;
    travlist->head->prev->next = toadd;
    toadd->prev = travlist->head->prev;
    travlist->head->prev = toadd;
    toadd->next = travlist->head;
    cout << "Song added" << endl;
    travlist->songnumber++;
    getchar();
}

void list::play(){
    char choice, choice2;
    int found = 0, indexchoice;
    playlist *travlist = head;
    song_node *trav;

    system("clear");
    cout << "PLAY >" << endl;
    cout << "Choose an option" << endl;
    cout << "L: Play a playlist" << endl;
    cout << "S: Play a playlist starting from a specific song" << endl;
    cout << "P: Play a single song" << endl;
    cout << "E: Exit" << endl << endl;
    cout << "Enter a choice: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if(choice == 'L' || choice == 'l'){
        char *temp = new char[LNAME_LENGTH];
        cout << "Enter the name of the playlist to play: ";
        cin.getline(temp, LNAME_LENGTH);
        //cin.ignore(1000, '\n');
        do{
            if(strcmp(travlist->name, temp)==0){
                found = 1;
                break;
            }
            travlist = travlist->next;
        }while(travlist != head);

        if(found == 0){
            cout << "Playlist not found" << endl;
            getchar();
            return;
        }
        trav = travlist->head;
        while(choice2 != 'E' && choice2 != 'e'){
            system("clear");
            cout << "PLAY > (Press N for Next, P for Previous, E for Exit)" << endl;
            cout << "playing..." << endl;
            cout << trav->data->name << " - " << trav->data->singer << " - " << trav->data->year << " - " << trav->data->style << endl;
            choice2 = getchar();
            cin.ignore(1000, '\n');

            if(choice2 == 'N' || choice2 == 'n')
                trav = trav->next;
            if(choice2 == 'P' || choice2 == 'p')
                trav = trav->prev;
        }
        delete[] temp;
    }

    else if(choice == 'S' || choice == 's'){
        int counter = 1;
        system("clear");
        cout << "PLAY >" << endl;
        do{
            cout << counter << ". " <<  travlist->name << endl;
            travlist = travlist->next;
            counter++;
        }while(travlist != head);
        cout << "Enter the index of the playlist: ";
        cin >> indexchoice;
        cin.ignore(1000, '\n');

        travlist = head;
        for(int i=1; i<indexchoice; i++){
            travlist = travlist->next;
        }

        trav = travlist->head;
        counter = 1;
        system("clear");
        cout << "PLAY >" << endl;
        do{
            cout << counter << ". " << trav->data->name << " - " << trav->data->singer << " - " << trav->data->year << " - " << trav->data->style << endl;
            counter++;
            trav = trav->next;
        }while(trav != travlist->head);
        cout << "Enter the index of the song: ";
        cin >> indexchoice;
        cin.ignore(1000, '\n');

        trav = travlist->head;
        for(int i=1; i<indexchoice; i++){
            trav = trav->next;
        }

        while(choice2 != 'E' && choice2 != 'e'){
            system("clear");
            cout << "PLAY > (Press N for Next, P for Previous, E for Exit)" << endl;
            cout << "playing..." << endl;
            cout << trav->data->name << " - " << trav->data->singer << " - " << trav->data->year << " - " << trav->data->style << endl;
            choice2 = getchar();
            cin.ignore(1000, '\n');

            if(choice2 == 'N' || choice2 == 'n')
                trav = trav->next;
            if(choice2 == 'P' || choice2 == 'p')
                trav = trav->prev;
        }
    }
    else if(choice == 'P' || choice == 'p'){
        int counter = 1;
        travlist = head->next;
        trav = travlist->head;
        system("clear");
        cout << "PLAY >" << endl;
        do{
            cout << counter << ". " << trav->data->name << " - " << trav->data->singer << " - " << trav->data->year << " - " << trav->data->style << endl;
            counter++;
            trav = trav->next;
        }while(trav != travlist->head);
        cout << "Enter index of the song you want to play: ";
        cin >> indexchoice;
        cin.ignore(1000, '\n');

        trav = travlist->head;
        for(int i=1; i<indexchoice; i++){
            trav = trav->next;
        }

        system("clear");
        cout << "PLAY >" << endl;
        cout << "playing..." << endl;
        cout << trav->data->name << " - " << trav->data->singer << " - " << trav->data->year << " - " << trav->data->style << endl;
        getchar();
    }
}

void list::removeSong(){
    int choice, counter = 1;
    playlist *travlist = head->next->next;
    song_node *trav;

    system("clear");
    while(travlist != head){
        cout << counter << ". " << travlist->name << endl;
        counter++;
        travlist = travlist->next;
    }
    travlist = head->next->next;
    cout << "Enter the index of the playlist to remove a song. Chronological and sorted playlists can't be deleted: ";
    cin >> choice; //We can't delete songs in chronological or sorted because these lists are used to create other lists or to add songs
    cin.ignore(1000, '\n');
    for(int i=1; i<choice; i++){
        travlist = travlist->next;
    }

    trav = travlist->head;
    counter = 1;

    do{
        cout << counter << ". " << trav->data->name << "\t" << trav->data->singer << "\t" << trav->data->year << "\t" << trav->data->style << endl;
        trav = trav->next;
        counter++;
    }while(trav != travlist->head);

    trav = travlist->head;
    cout << "Enter the index of the song you want to remove: ";
    cin >> choice;
    cin.ignore(1000, '\n');
    for(int i=1; i<choice; i++){
        trav = trav->next;
    }
    if(choice == 1)
        travlist->head = travlist->head->next; //Moving the head if the user wants to delete the first song.

    trav->prev->next = trav->next;
    trav->next->prev = trav->prev;

    delete trav;

    cout << "Song removed" << endl;
    travlist->songnumber--;
    getchar();

}

void list::deleteList(){
    playlist *travlist = head->next->next;
    int counter = 1, choice;

    system("clear");

    while(travlist != head){
        cout << counter << ". " << travlist->name << endl;
        counter++;
        travlist = travlist->next;
    }
    cout << "Enter the index of the playlist you want to delete(Chronological and sorted lists can't be deleted): ";
    cin >> choice;
    cin.ignore(1000, '\n');
    travlist = head->next->next;

    for(int i=1; i<choice; i++){//positioning the pointer to the playlist user wants to delete
        travlist = travlist->next;
    }

    for(int i=1; i<travlist->songnumber; i++){//Deleting the song nodes of the playlist;
        travlist->head = travlist->head->next;
        delete travlist->head->prev;
    }
    delete travlist->head;

    travlist->prev->next = travlist->next;
    travlist->next->prev = travlist->prev;

    delete[] travlist->name;
    delete travlist;

    cout << "Playlist deleted" << endl;
    playlist_count--;
    getchar();
}

void list::printList(){
    playlist *travlist = head;
    playlist *printlist = head;
    song_node *trav, *toadd;
    int counter = 1, counter2 = 1, indexcounter = 1, indexchoice;
    char choice, choice2, playChoice;


    while(choice != 'E' && choice != 'e'){
        system("clear");
        cout << "PLAYLISTS :" << endl;

        do{
            cout << counter << ". " << printlist->name << endl;
            counter++;
            printlist = printlist->next;
        }while(printlist != head);
        printlist = head;
        counter = 1;

        cout << endl << counter2 << ". " << travlist->name << endl;
        cout << "N(Next) - P(Previous) - S(Select) - E(Exit)" << endl;
        cin >> choice;
        cin.ignore(1000, '\n');

        if(choice == 'N' || choice == 'n'){
            travlist = travlist->next;

            if(counter2 >= playlist_count)
                counter2 = 1;
            else
                counter2++;
        }
        else if(choice == 'P' || choice == 'p'){
            travlist = travlist->prev;
            if(counter2 == 1)
                counter2 = playlist_count;
            else
                counter2--;
        }
        else if(choice == 'S' || choice == 's'){
            cout << "D(Delete Playlist) - A(Add Song) - R(Remove Song) - P(Play Playlist)" << endl;
            cin >> choice2;
            cin.ignore(1000, '\n');

            if(choice2 == 'D' || choice2 == 'd'){
                if(travlist == head || travlist == head->next){
                    cout << "Chronological and sorted lists can't be deleted because it will cause data loss" << endl;
                    getchar();
                }
                else{
                    for(int i=1; i<travlist->songnumber; i++){//Deleting the song nodes of the playlist;
                        travlist->head = travlist->head->next;
                        delete travlist->head->prev;
                    }
                    delete travlist->head;

                    travlist->prev->next = travlist->next;
                    travlist->next->prev = travlist->prev;

                    delete[] travlist->name;
                    delete travlist;

                    cout << "Playlist deleted" << endl;
                    playlist_count--;
                    getchar();
                    return;
                }
            }

            else if(choice2 == 'A' || choice2 == 'a'){
                if(travlist == head || travlist == head->next || travlist == head->next->next){
                    cout << "You can't add songs to chronological, sorted and random lists" << endl;
                    getchar();
                }
                else{
                    trav = head->next->head;
                    do{
                        cout << indexcounter << ". " << trav->data->name << "\t" << trav->data->singer << "\t" << trav->data->year << "\t" << trav->data->style << endl;
                        trav = trav->next;
                        indexcounter++;
                    }while(trav != head->next->head);
                    cout << "Enter index of the song you want to add: ";
                    cin >> indexchoice;
                    cin.ignore(1000, '\n');
                    trav = head->next->head;
                    for(int i=1; i<indexchoice; i++){
                        trav = trav->next;
                    }
                    toadd = new song_node;
                    toadd->parent = travlist;
                    toadd->data = trav->data;
                    travlist->head->prev->next = toadd;
                    toadd->prev = travlist->head->prev;
                    travlist->head->prev = toadd;
                    toadd->next = travlist->head;
                    cout << "Song added" << endl;
                    travlist->songnumber++;
                    getchar();
                    return;
                }
            }

            else if(choice2 == 'R' || choice2 == 'r'){
                if(travlist == head || travlist == head->next){
                    cout << "You can't remove songs from Chronological or Sorted lists because it will cause data loss" << endl;
                    getchar();
                }
                else{
                    trav = travlist->head;

                    do{
                        cout << indexcounter << ". " << trav->data->name << "\t" << trav->data->singer << "\t" << trav->data->year << "\t" << trav->data->style << endl;
                        trav = trav->next;
                        indexcounter++;
                    }while(trav != travlist->head);

                    trav = travlist->head;
                    cout << "Enter the index of the song you want to remove: ";
                    cin >> indexchoice;
                    cin.ignore(1000, '\n');
                    for(int i=1; i<indexchoice; i++){
                        trav = trav->next;
                    }
                    if(indexchoice == 1)
                        travlist->head = travlist->head->next; //Moving the head if the user wants to delete the first song.

                    trav->prev->next = trav->next;
                    trav->next->prev = trav->prev;

                    delete trav;

                    cout << "Song removed" << endl;
                    travlist->songnumber--;
                    getchar();
                    return;
                }
            }

            else if(choice2 == 'P' || choice2 == 'p'){
                trav = travlist->head;
                while(playChoice != 'E' && playChoice != 'e'){
                    system("clear");
                    cout << "PLAY >" << endl;
                    cout << "playing..." << endl;
                    cout << trav->data->name << " - " << trav->data->singer << " - " << trav->data->year << " - " << trav->data->style << endl;
                    cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
                    cin >> playChoice;
                    cin.ignore(1000, '\n');

                    if(playChoice == 'N' || playChoice == 'n'){
                        trav = trav->next;
                    }
                    else if(playChoice == 'P' || playChoice == 'p'){
                        trav = trav->prev;
                    }
                }
                return;
            }

        }
    }

}

void list::writeToFile(){
    playlist *travlist = head->next->next->next;
    song_node *trav;

    if(!(database = fopen("songbook.txt", "w+"))){//Opening the file
        cerr << "File can not be opened" << endl;
        exit(1);
    }
    trav = head->head;
    do{
        fprintf(database, "%s\t%s\t%d\t%s\r\n", trav->data->name, trav->data->singer, trav->data->year, trav->data->style);
        trav = trav->next;
    }while(trav != head->head);

    while(travlist != head){
        fprintf(database, "*****\r\n");
        fprintf(database, "%s\r\n", travlist->name);
        trav = travlist->head;

        do{
            fprintf(database, "%s\t%s\t%d\t%s\r\n", trav->data->name, trav->data->singer, trav->data->year, trav->data->style);
            trav = trav->next;
        }while(trav != travlist->head);
        travlist = travlist->next;
    }
    fclose(database);
}

void list::Exit(){
    playlist *travlist;

    writeToFile();

    for(int i=0; i<playlist_count-1; i++){
        travlist = head->next;

        for(int i=1; i<travlist->songnumber; i++){//Deleting the song nodes of the playlist;
            travlist->head = travlist->head->next;
            delete travlist->head->prev;
        }
        delete travlist->head;

        travlist->prev->next = travlist->next;
        travlist->next->prev = travlist->prev;

        delete[] travlist->name;
        delete travlist;
    }

    for(int i=1; i<head->songnumber; i++){
        head->head = head->head->next;
        delete[] head->head->prev->data->name;
        delete[] head->head->prev->data->singer;
        delete[] head->head->prev->data->style;
        delete head->head->prev->data;
        delete head->head->prev;
    }
    delete[] head->head->data->name;
    delete[] head->head->data->singer;
    delete[] head->head->data->style;
    delete head->head->data;
    delete head->head;

    delete[] head->name;
    delete head;
}
