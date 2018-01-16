//Onat Şahin  No:150150129  mail:sahino15@itu.edu.tr

#include "structures.h"
using namespace std;

void readAndParse(std::string fileName, vector<BookChar>& list);
void writeToFile(std::string fileName, vector<BookChar>& list);

int main(int argc, const char * argv[]) {
    
    vector<BookChar> inputList;
    Dictionary dict;
    List list;
    clock_t beginTime=0, endTime=0;
    
    readAndParse("ds-set-input.txt", inputList); // Read the file, the convert the lines to character objects, store them to the inputList vector
    
    cout << endl << "DICTIONARY" << endl;
    
    beginTime = clock();
    
    for(int i=0; i<inputList.size(); i++){ //Insert the objects in inputList to the dictionary
        dict.insertion(inputList[i], i);
    }
    
    endTime = clock();
    
    cout << "Insertion finished after " << ( (float)(endTime - beginTime) )/CLOCKS_PER_SEC << " seconds." << endl << endl;
    
    dict.collusionPrint();
    
    beginTime=0;
    endTime=0;
    
    readAndParse("ds-set-lookup.txt", inputList); //Read the file, the convert the lines to character objects, store them to the inputList vector.
    
    beginTime = clock();
    
    for(int i=0; i<inputList.size(); i++){ // Search for the characters that belong to the objects in the inputList from the dictionary
        dict.lookup(inputList[i]);
    }
    
    endTime = clock();
    
    cout << endl << "Lookup finished after " << ( (float)(endTime - beginTime) )/CLOCKS_PER_SEC << " seconds." << endl << endl;
    
    writeToFile("ds-set-output-dict.txt", inputList);
    
    readAndParse("ds-set-input.txt", inputList);
    
    beginTime=0;
    endTime=0;
    
    cout << "LIST" << endl;
    
    beginTime = clock(); // Same operations as the operations done on the dictionary
    
    for(int i=0; i<inputList.size(); i++){
        list.insertion(inputList[i]);
    }
    
    endTime = clock();
    
    cout << "Insertion finished after " << ( (float)(endTime - beginTime) )/CLOCKS_PER_SEC << " seconds." << endl;
    
    beginTime=0;
    endTime=0;
    
    readAndParse("ds-set-lookup.txt", inputList);
    
    beginTime = clock();
    
    for(int i=0; i<inputList.size(); i++){
        list.lookup(inputList[i]);
    }
    
    endTime = clock();
    
    cout << "Lookup finished after " << ( (float)(endTime - beginTime) )/CLOCKS_PER_SEC << " seconds." << endl << endl;
    
    writeToFile("ds-set-output-list.txt", inputList);
    
    return 0;
}

void readAndParse(std::string fileName, vector<BookChar>& list){
    std::ifstream inputFile(fileName);
    std::string charData, data;
    unsigned int numbers[3];
    unsigned long dividerPos;
    
    list.clear();
    
    while(getline(inputFile, charData)){ //While there is a line to read; read the line, parse, create a character object, store the object in the input vector
        
        if(charData[charData.size()-1] == '\r')
            charData = charData.substr(0, charData.size()-1);
        
        for(int i=0; i<3; i++){
            dividerPos = charData.find('\t');
            numbers[i] = stoi( charData.substr(0, dividerPos) );
            charData.erase(0, dividerPos+1);
        }
        if(fileName == "ds-set-input.txt"){
            data = charData/*.substr(0, charData.size()-1)*/;
            list.push_back(BookChar(numbers[0], numbers[1], numbers[2], data));
        }
        else
            list.push_back(BookChar(numbers[0], numbers[1], numbers[2], ""));
    }
    inputFile.close();
}

void writeToFile(std::string fileName, vector<BookChar>& list){ // Write the list into the file
    std::ofstream output(fileName);
    
    for(int i=0; i<list.size(); i++){
        output << list[i].getPageNo() << '\t' << list[i].getLineNo() << '\t' << list[i].getIndexNo() << '\t' << list[i].getCharacter() << "\n";
    }
    output.close();
}

