// arrayoperations.cpp
// Defining the operations that we can perform on the array

#include <iostream> // allows program to perform input and output
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // program uses C++ standard string class
#include <iomanip>

#include "arrayoperations.h" // include definition of struct Array

using namespace std; // enables the program to use all the names in any included standard C++ header

// create an empty array
void Array::create()

{
    bool read = true;
    filename = "phonebook.txt";
    phonebook = fopen(filename,"r+");
    if(!phonebook){
        read = false;
        if(!(phonebook = fopen(filename,"w+"))){
            numrecords = 0; // the number of records in the list is initially 0
            cerr<< "Can not open file"<<endl;
            exit(1);
        }
    }
    if(read){
        fseek(phonebook,0,SEEK_SET);
        fread(&numrecords,sizeof(int),1,phonebook);
        //fscanf(phonebook,"%d",&numrecords);
        for(int i = 0; i < numrecords ; i++){
            //fscanf(phonebook,"%s %s",r[i].name,r[i].phonenum);
            fread(&r[i],sizeof(Phone_Record),1,phonebook);
        }
    }
}

// add new phone record into array
void Array::add(Phone_Record *nrptr)
{
    int i;
	unsigned int j=1,k=1;
	int writeIndex=0;
	for(i = 0 ; i < numrecords ; i++){
        if(tolower(*((r+i))->name) < tolower( *(nrptr->name) )){//Move further.
            writeIndex++;
        }
        if(tolower(*((r+i))->name)== tolower( *(nrptr->name) )){
            for(j = 1 ; j < sizeof(nrptr->name) || k < sizeof( *((r+i)->name) );j++,k++){
            	
                if(tolower( *((r+i)->name+j) ) == tolower( *(nrptr->name+k) ))continue;

                if(tolower( *((r+i)->name+j) ) < tolower(*(nrptr->name+k))){
                    writeIndex++;
                    break;
                }
                if(tolower(  *((r+i)->name+j) )  > tolower(*(nrptr->name+k))){
                    break;
                }
            }
        }
        if( tolower(*((r+i))->name) > tolower( *(nrptr->name) ) ){//Here write.
            break;
        }
	}
	numrecords++; // increment the number of records in the list
    for(i = numrecords-1 ; i > writeIndex ; i--){
       /* strcpy(r[i].name, r[i-1].name);
        strcpy(r[i].phonenum, r[i-1].phonenum);*/
        *(r+i) = *(r+i-1);
    }
	// add the new record as the last element (into position "numrecords")
	strcpy( (r+writeIndex)->name, nrptr->name);
	strcpy( (r+writeIndex)->phonenum, nrptr->phonenum);

	 

}

// search the array for a name
int Array::search(char target[])
{
	int counter = 0;
	bool all = false;
	int found = 0;

	if ( strcmp(target, "*") == 0 ) { // compare the string target to the string "*", if they are equal do the following
		all = true;
	}
	for (int i = 0; i < numrecords; i++) {
		// if( strcmp(r[i].name, target) == 0 ) {
		if( all || strncmp(r[i].name, target, strlen(target)) == 0 ){
			cout << i + 1 << ". " << r[i].name << "    \t" << r[i].phonenum << endl;
			found++;
		}
	}
	return found;
}

// remove the name and phonenum fields of a phone record in the array in position "recordnum - 1"
// by replacing it with an empty record
void Array::remove(int recordnum)
{
	Phone_Record temp;
	strcpy(temp.name, "");
	strcpy(temp.phonenum, "");
	r[recordnum - 1] = temp;
}

// update the name and phonenum fields of a phone record in the array in position "recordnum - 1"
void Array::update(int recordnum, Phone_Record *nrptr)
{
    int i;
	unsigned int j=1,k=1;
	int writeIndex=0;
	for(i = 0 ; i < numrecords ; i++){
        if(tolower(*((r+i))->name) < tolower( *(nrptr->name) )){//Move further.
            writeIndex++;
        }
        if(tolower(*((r+i))->name)== tolower( *(nrptr->name) )){
            for(j = 1 ; j < sizeof(nrptr->name) || k < sizeof( *((r+i)->name) );j++,k++){
            	
                if(tolower( *((r+i)->name+j) ) == tolower( *(nrptr->name+k) ))continue;

                if(tolower( *((r+i)->name+j) ) < tolower(*(nrptr->name+k))){
                    writeIndex++;
                    break;
                }
                if(tolower(  *((r+i)->name+j) )  > tolower(*(nrptr->name+k))){
                    break;
                }
            }
        }
        if( tolower(*((r+i))->name) > tolower( *(nrptr->name) ) ){//Here write.
            break;
        }
	}
	for(i = numrecords-1 ; i > writeIndex ; i--){
       /* strcpy(r[i].name, r[i-1].name);
        strcpy(r[i].phonenum, r[i-1].phonenum);*/
        if(i==recordnum)continue;
        *(r+i) = *(r+i-1);
    }
	// add the new record as the last element (into position "numrecords")
	strcpy( (r+writeIndex)->name, nrptr->name);
	strcpy( (r+writeIndex)->phonenum, nrptr->phonenum);

	 
	
}

// print to the screen a listing of records in the array
void Array::list()
{
	for (int i = 0; i <
	 numrecords; i++)
		cout << i + 1 << ". " << r[i].name << "    \t" << r[i].phonenum << endl;
}
