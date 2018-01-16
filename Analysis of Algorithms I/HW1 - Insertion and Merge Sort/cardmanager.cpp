#include "cardmanager.h"

Card::Card(std::string nname, std::string nclass, std::string nrarity, std::string nset, std::string ntype, int ncost){
    name = nname;
    Class = nclass;
    rarity = nrarity; // Constructor for Card objects
    set = nset;
    type = ntype;
    cost = ncost;
}

CardManager::CardManager(char* inputFileName){ //Constructor for Card Manager
    std::ifstream inputFile(inputFileName); //Opening the input file
    std::string cardData;
    unsigned long wordBegin, wordEnd;
    int cardCost;
    std::vector<std::string> parsedData(6);
    
    while(getline(inputFile, cardData)){ //Parsing each line
        if( cardData[cardData.length()-1] == '\r' )
            cardData = cardData.substr(0,cardData.length()-1);
        
        wordEnd = -1;
        for(int i=0; i<6; i++){
            wordBegin = wordEnd+1;
            wordEnd = cardData.find('\t', wordBegin);
            parsedData[i] = cardData.substr(wordBegin, wordEnd-wordBegin);
        }
        
        if(parsedData[5].length() == 1) //Converting cost from string to integer
            cardCost = parsedData[5][0] - '0';
        else
            cardCost = (parsedData[5][0] - '0')*10 + (parsedData[5][1]-'0');
            
        
        cardList.push_back(Card(parsedData[0], parsedData[1], parsedData[2], parsedData[3], parsedData[4], cardCost)); //Creating a Card object and pushing it to the list
    }
    temp.resize(cardList.size()); //resizing the temp vector for merge sort
    inputFile.close(); //closing the file
}

int CardManager::strCompare(std::string first, std::string second) const{
    unsigned long len1 = first.length(); //String comparison function according to the order in the files
    unsigned long len2 = second.length();
    int i,j;
    char firstc, secondc;
    
    for(i=0,j=0; i<len1 && j<len2; i++,j++){
        if(first[i] > 32 && first[i] < 48 && first[i] != 44)
            i++;
        if(second[j] > 32 && second[j] < 48 && second[j] != 44){
            j++;
        }
        
        if(first[i] >= 'A' && first[i] <= 'Z')
            firstc = first[i] + 32;
        else firstc = first[i];
        
        if(second[j] >= 'A' && second[j] <= 'Z')
            secondc = second[j] + 32;
        else secondc = second[j];
        
        if(firstc > secondc)
            return 1;
        else if(firstc < secondc)
            return -1;
    }
    if(len1 < len2)
        return -1;
    else if(len2 < len1)
        return 1;
    else return 0;
    
}

int CardManager::fullCompare(const Card& first, const Card& second) const{
    if(first.Class > second.Class) //Card object comparison function according to full sort
        return 1;
    else if(first.Class < second.Class)
        return -1;
    else if(first.cost > second.cost)
        return 1;
    else if(first.cost < second.cost)
        return -1;
    else if(strCompare(first.name, second.name) > 0)
        return 1;
    else if(strCompare(first.name, second.name) < 0)
        return -1;
    else return 0;
}

int CardManager::filterCompare(const Card &first, const Card &second) const{
    if(first.type.compare(second.type) > 0) //Card object comparison function according to filter sort
        return 1;
    else if(first.type.compare(second.type) < 0)
        return -1;
    else return 0;
}

float CardManager::fullSort(const char algorithm){ //Full sort
    Card current;
    clock_t begin = 0, end = 0;
    
    // INSERTION SORT ######################################################################################
    if(algorithm == 'i'){
        begin = clock();
        int j;
        for(int i=1; i<cardList.size(); i++){
            current = cardList[i];
            for(j = i-1; j>=0 && fullCompare(current, cardList[j]) == -1; j--){
                cardList[j+1] = cardList[j];
            }
            cardList[j+1] = current;
        }
        end = clock();
    }
    
    // MERGE SORT #########################################################################################
    else if(algorithm == 'm'){
        begin = clock();
        mergeSort(0, (int)cardList.size()-1, 'u');
        end = clock();
    }
    //#####################################################################################################
    
    return (float)(end - begin)/CLOCKS_PER_SEC;
}

float CardManager::filterSort(const char algorithm){
    Card current;
    long begin = 0, end = 0;
    
    // INSERTION SORT ######################################################################################
    if(algorithm == 'i'){
        begin = clock();
        int j;
        for(int i=1; i<cardList.size(); i++){
            current = cardList[i];
            for(j = i-1; j>=0 && filterCompare(current, cardList[j]) == -1; j--){
                cardList[j+1] = cardList[j];
            }
            cardList[j+1] = current;
        }
        end = clock();
    }
    
    // MERGE SORT #########################################################################################
    else if(algorithm == 'm'){
        begin = clock();
        mergeSort(0, (int)cardList.size()-1, 'i');
        end = clock();
    }
    //#####################################################################################################
    
    return (float)(end - begin)/CLOCKS_PER_SEC;
}

void CardManager::mergeSort(int begin, int end, const char &algorithm){
    if(begin < end){
        int mid = (begin + end)/2;
        mergeSort(begin, mid, algorithm);
        mergeSort(mid+1, end, algorithm);
        merge(begin, mid, end, algorithm);
    }
}

void CardManager::merge(int begin, int mid, int end, const char &algorithm){
    int size1 = mid - begin + 1;  //Instead of the merge algorithm described in the lecture slides which creates 2 new arrays and splits the
    int size2 = end - mid;        //main array, I decided to use the main array without splitting it by keeping track of the begin
    int i,j,tempIndex;            //and end indexes of 2 halves make the algorithm faster. The merges are made into the temp array
                                  //created before, which is copied to main array in the end. This avoids allocating and freeing new memory
    i= begin;                     //every time the function is called.
    j= mid+1;
    
    if(algorithm == 'u'){ //merge for full sort
        for(int k=0; k < size1 + size2; k++){
            if(i == mid+1){
                for(int l=j; l<end+1; l++, k++){
                    temp[k] = cardList[l];
                }
                break;
            }
            else if(j == end+1){
                for(int l=i; l<mid+1; l++, k++){
                    temp[k] = cardList[l];
                }
                break;
            }
            else if(fullCompare(cardList[i], cardList[j]) == -1){
                temp[k] = cardList[i];
                i++;
            }
            else{
                temp[k] = cardList[j];
                j++;
            }

        }
    }
    else if(algorithm == 'i'){ //merge for filter sort
        for(int k=0; k < size1 + size2; k++){
            if(i == mid+1){
                for(int l=j; l<end+1; l++, k++){
                    temp[k] = cardList[l];
                }
                break;
            }
            else if(j == end+1){
                for(int l=i; l<mid+1; l++, k++){
                    temp[k] = cardList[l];
                }
                break;
            }
            else if(filterCompare(cardList[i], cardList[j]) == -1){
                temp[k] = cardList[i];
                i++;
            }
            else{
                temp[k] = cardList[j];
                j++;
            }
            
        }
    }
    for(int i=begin, tempIndex=0; i<=end; i++, tempIndex++){
        cardList[i] = temp[tempIndex];
    }
}

void CardManager::writeToFile(char* outputFile){
    std::ofstream output(outputFile);
    
    for(int i=0; i< cardList.size(); i++){
        output << cardList[i].name << '\t' << cardList[i].Class << '\t' << cardList[i].rarity << '\t' << cardList[i].set << '\t' << cardList[i].type << '\t' << cardList[i].cost << "\r\n";
    }
    output.close();
}


















