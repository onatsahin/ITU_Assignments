//Onat ŞAHİN No: 150150129

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "shop.h"
#include "candy.h"
#include "cookie.h"
#include "icecream.h"

using namespace std;

void FileCheckout();//Function to handle file operations

int main()
{
    Cookie cookie1("Chocolate Chip Cookies",10, 180);

    Cookie cookie2("Cake Mix Cookies", 16, 210);
    Shop<Cookie> cookieShop(cookie1);
    cookieShop.add(cookie2);
    cout<<cookieShop<<endl;

    try{
        cout << cookieShop[2] << endl;
    }
    catch(const string error){
        cout << error << endl;
    }

    Icecream icecream1("Chocolate ice cream",1.5, 170);

    Shop<Icecream> icecreamShop(icecream1);
    cout<<icecreamShop<<endl;

    try{
        icecreamShop.setDiscount(50);
    }
    catch(const string error){
        cout << error << endl;
    }

    Candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
    Candy candy3("Hanukkah gelt",8,110);
    Shop<Candy> candyShop(candy2);
    candyShop.add(candy3);
    candyShop.setDiscount(15);

    cout<<candyShop<<endl;

    try{
        FileCheckout();
    }
    catch(const string error){
        cout << error << endl;
    }

    return 0;
}

void FileCheckout(){
    Shop<Cookie> cookieStock; //Shops for each type to keep the stock
    Shop<Candy> candyStock;
    Shop<Icecream> icecreamStock;

    std::string name; //Variables
    int type;
    float itemCount;
    float price;
    int tokenBegin = 0,i;

    ifstream file("stock.txt");

    if(!file.is_open()) // An exception is thrown if the file is not opened successfully
        throw "File could not be opened";

    file.seekg(27);
    std::string line;

    while(getline(file, line)){ //Loop continues until all lines are read
        if( line[line.length()-1] == '\r' )
            line = line.substr(0,line.length()-1); //Cleaning the \r and \n characters in the end of the lines

        i = tokenBegin;

        while(line[i] != '\t')  //By keeping track of the positions of \t characters, the string is parsed with substr function
            i++;

        name = line.substr(tokenBegin,i);
        i++;
        type = line[i] - '0';
        tokenBegin = i+2;

        while(line[i] != '\t'){
            i++;
        }

        i++;

        while(line[i] != '\t'){
            i++;
        }

        itemCount = atof(line.substr(tokenBegin, i-tokenBegin).c_str()); //type conversion from std::string to float
        i += 1;
        tokenBegin = i;
        price = atof(line.substr(tokenBegin, line.length()-tokenBegin).c_str());

        if(type == 1) // Adding to the stock
            cookieStock.add(Cookie(name,itemCount,price));
        else if(type == 2)
            candyStock.add(Candy(name,itemCount,price));
        else
            icecreamStock.add(Icecream(name,itemCount,price));

        i=0;
        tokenBegin=0;
    }

    file.close();
    file.open("order.txt"); //order file is opened for reading the order

    vector<string> err; //vector to store "We don't have enough" messages
    vector<string> item; //Vector to store the lines of bought items
    bool found;
    int numOfItems=0,index;
    float totalCost=0;
    float itemCost;
    std::ostringstream itemCountStr, itemCostStr, numOfItemsStr; //String streams are used to convert the substrings from order lines to floats

    while(getline(file, line)){
        if( line[line.length()-1] == '\r' ) //Reading and parsing
            line = line.substr(0,line.length()-1);

        i = tokenBegin;

        while(line[i] != '\t')
            i++;

        name = line.substr(tokenBegin,i);
        i++;
        type = line[i] - '0';
        tokenBegin = i+2;

        itemCount = atof(line.substr(tokenBegin, line.length()-tokenBegin).c_str());

        i=0;
        tokenBegin=0;
        found = false;

        itemCountStr.str("");
        itemCountStr << itemCount;

        if(type == 1){ //According to the type, ordered item is searched in the appropriate shop
            for(int i=0; i<cookieStock.getSize(); i++){
                if(name == cookieStock[i].getName()){
                    found = true;
                    index = i;
                    numOfItems++;
                    break;
                }
            }
            if(found){ //Checking the number of the item ordered in the stock
                if(itemCount > cookieStock[index].getQuantity()){
                    err.push_back("!!! We don't have " + itemCountStr.str() + " (" + name + ")" + "s.");
                    itemCount = cookieStock[index].getQuantity();
                }
                itemCost = cookieStock[index].getPricePerDozen() / 12 * itemCount;
            }
        }
        else if(type == 2){
            for(int i=0; i<candyStock.getSize(); i++){
                if(name == candyStock[i].getName()){
                    found = true;
                    index = i;
                    numOfItems++;
                    break;
                }
            }
            if(found){
                if(itemCount > candyStock[index].getQuantity()){
                    err.push_back("!!! We don't have " + itemCountStr.str() + " (" + name + ")" + "s.");
                    itemCount = candyStock[index].getQuantity();
                }
                itemCost = candyStock[index].getPricePerKg() * itemCount;
            }
        }
        else{
            for(int i=0; i<icecreamStock.getSize(); i++){
                if(name == icecreamStock[i].getName()){
                    found = true;
                    index = i;
                    numOfItems++;
                    break;
                }
            }

            if(found){
                if(itemCount > icecreamStock[index].getQuantity()){
                    err.push_back("!!! We don't have " + itemCountStr.str() + " (" + name + ")" + "s.");
                    itemCount = icecreamStock[index].getQuantity();
                }
                itemCost = icecreamStock[index].getPricePerLitre() * itemCount;
            }
        }

        if(!found){ // If the item is not found, appropriate message is stored in the err vector
            err.push_back("!!! We don't have " + itemCountStr.str() + " (" + name + ")" + "s.");
        }
        else{
            itemCountStr.str(""); //item message is created and stored in the item vector
            itemCostStr.str("");
            numOfItemsStr.str("");
            itemCountStr << itemCount;
            itemCostStr << itemCost;
            numOfItemsStr << numOfItems;
            totalCost += itemCost;
            item.push_back(numOfItemsStr.str() + ": " + name + " #" + itemCountStr.str() + " Cost: " + itemCostStr.str());
        }
    }
    file.close();
    ofstream checkout("checkout.txt"); // using ofstream, everything is printed

    totalCost = totalCost / 100 * 108;

    for(unsigned int i=0; i<err.size(); i++)
        checkout << err[i] << std::endl;

    checkout << "-----------------------" << std::endl;
    checkout << "Number of items: " << numOfItems << std::endl;

    for(unsigned int i=0; i<item.size(); i++)
        checkout << item[i] << std::endl;


    checkout << "**********************" << std::endl;
    checkout << "Total Cost: " << totalCost << std::endl;
    checkout << "Discount: %10" << std::endl;
    checkout << "Discount amount: -" << totalCost / 10 << std::endl; //Calculations are made
    checkout << "Discounted amount: " << totalCost / 10 * 9 << std::endl;
    checkout << "**********************" << std::endl;
}

