//Onat Şahin  No:150150129  mail:sahino15@itu.edu.tr

#include "structures.h"

//#### BOOKCHAR ##############################################################

BookChar::BookChar(unsigned int page, unsigned int line, unsigned int index, std::string c){ //Constructor
    pageNo = page;
    lineNo = line;
    indexNo = index;
    character = c;
    key = (pageNo*10000) + (lineNo*100) + indexNo; //Generating the key;
}

unsigned int BookChar::getPageNo(){ // Getters
    return pageNo;
}

unsigned int BookChar::getLineNo(){
    return lineNo;
}

unsigned int BookChar::getIndexNo(){
    return indexNo;
}

std::string BookChar::getCharacter(){
    return character;
}

//#### DICTIONARY ############################################################

Dictionary::Dictionary(){
    for(int i=0; i<TABLE_SIZE; i++){
        occupied[i] = false; // Initializing the boolean array to false
    }
    collisionCount[3] = 0;
}

void Dictionary::insertion(BookChar& toAdd, int order){
    
    bool inserted=false;
    double temp;
    unsigned int iParameter=0, tableIndex;
    
    while(!inserted){
        temp = toAdd.key * 0.618; // Implementation of the hash function and the probing function
        tableIndex = fmod((floor(TABLE_SIZE*fmod(temp,1)) + (7*iParameter) + (3*iParameter*iParameter)), TABLE_SIZE);
        
        if(!occupied[tableIndex]){ // If the spot is not occupied, insert the char object to the table
            table[tableIndex] = toAdd;
            inserted = true;
            occupied[tableIndex] = true;
        }
        else{ // If the spot is occupied, increment i and hash once again
            iParameter++;
            collisionCount[3]++; // Collision counted
        }
    }
    if(order+1 == 1000){ // keeping track of the number of collisions for 1000,10000 and 100000
        collisionCount[0] = collisionCount[3];
    }
    else if(order+1 == 10000){
        collisionCount[1] = collisionCount[3];
    }
    else if(order+1 == 100000){
        collisionCount[2] = collisionCount[3];
    }
    
}

void Dictionary::lookup(BookChar &toSearch){
    
    bool found=false;
    double temp;
    unsigned int iParameter=0, tableIndex;
    
    while(!found){
        temp = toSearch.key * 0.618; // Use the hashing and probing to find the index
        tableIndex = fmod((floor(TABLE_SIZE*fmod(temp,1)) + (7*iParameter) + (3*iParameter*iParameter)), TABLE_SIZE);
        
        if(toSearch.key == table[tableIndex].key){ // If the character is the one we want, copy the character to the input object
            toSearch.character = table[tableIndex].character;
            found = true;
        }
        else{ // If not, increment i and hash once again
            iParameter++;
        }
    }
    
}

void Dictionary::collusionPrint(){
    std::cout << "Average number of collisions (first 1,000)   |" << (float)collisionCount[0]/1000 << std::endl;
    std::cout << "Average number of collisions (first 10,000)  |" << (float)collisionCount[1]/10000 << std::endl;
    std::cout << "Average number of collisions (first 100,000) |" << (float)collisionCount[2]/100000 << std::endl;
    std::cout << "Average number of collisions (overall)       |" << (float)collisionCount[3]/131070 << std::endl;
    //std::cout << "Total collision: " << collisionCount[3] << std::endl;
    
}

//#### LIST #######################################################################

// Classic linked list implementation

ListNode::ListNode(BookChar& newChar){
    data = newChar;
    next = NULL;
}

List::List(){
    head = NULL;
    tail = NULL;
}

List::~List(){
   
    ListNode *toDelete;
    
    while(head){
        toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

void List::insertion(BookChar &toAdd){
    
    ListNode *newNode = new ListNode(toAdd);
    
    if(!head){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    
}

void List::lookup(BookChar& toSearch){
    ListNode *trav = head;
    
    while(trav){
        if(trav->data.key == toSearch.key){
            toSearch.character = trav->data.character;
            break;
        }
        trav = trav->next;
    }
    
}









