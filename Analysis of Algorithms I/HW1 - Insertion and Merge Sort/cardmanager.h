#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <cctype>
#include <ctime>

class Card{
    friend class CardManager;
    std::string name, Class, rarity, set, type;
    int cost;
public:
    Card(){}; //Constructors
    Card(std::string, std::string, std::string, std::string, std::string, int);
};

class CardManager{
    std::vector<Card> cardList; //List of Cards
    std::vector<Card> temp;     //Temporary list for merge function (Explained in merge function)
    int strCompare(std::string, std::string) const;  //Function to compare strings according to the order in the list files
    int fullCompare(const Card&, const Card&) const; //Function to compare Card objects according to full sort
    int filterCompare(const Card&, const Card&) const; // //Function to compare Card objects according to filter sort
    void mergeSort(int, int, const char&);
    void merge(int, int, int, const char&);
public:
    CardManager(char*);
    float fullSort(const char);
    float filterSort(const char);
    void writeToFile(char*);
};

#endif // CARDMANAGER_H

