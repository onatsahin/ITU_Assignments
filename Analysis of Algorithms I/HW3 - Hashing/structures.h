//Onat Şahin  No:150150129  mail:sahino15@itu.edu.tr

#ifndef structures_h
#define structures_h
#define TABLE_SIZE 131071

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>

class BookChar{ // Book character class
    friend class Dictionary;
    friend class List;
    unsigned int pageNo, lineNo, indexNo;
    std::string character; //I used string to keep the char to be able to read non-ascii characters
    unsigned long key; //Key generated from the values
public:
    BookChar(){}; //Default constructor
    BookChar(unsigned int,unsigned int,unsigned int,std::string);
    unsigned int getPageNo(); // getters for my print function in the main
    unsigned int getLineNo();
    unsigned int getIndexNo();
    std::string getCharacter();
};

class Dictionary{
    BookChar table[TABLE_SIZE]; // Hash table
    bool occupied[TABLE_SIZE]; // Boolean array to keep track of occupied spots in the table
    unsigned int collisionCount[4]; // Array for collision counting
public:
    Dictionary();
    void insertion(BookChar&, int);
    void lookup(BookChar&);
    void collusionPrint();
};

class ListNode{  //Classic linked list implementation
    friend class List;
    BookChar data;
    ListNode *next;
public:
    ListNode(BookChar&);
};

class List{
    ListNode *head;
    ListNode *tail;
public:
    List();
    ~List();
    void insertion(BookChar&);
    void lookup(BookChar&);
};

#endif /* structures_h */

