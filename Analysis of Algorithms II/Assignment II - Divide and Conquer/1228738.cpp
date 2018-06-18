//Onat Şahin 150150129. Since the code uses stoi(), compile with -std=c++11 flag
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Ball{ //Ball class
    int x;
    int y;
    int z;
public:
    Ball(int nx, int ny, int nz): x(nx), y(ny), z(nz) {};
    int getX() const{ return x; };
    int getY() const{ return y; };
    int getZ() const{ return z; };
};


void readToArray(char* filename, vector<Ball>& list);
float calculateDistance(Ball& A, Ball &B);
bool compareByX(const Ball& A, const Ball& B);
bool compareByY(const Ball& A, const Ball& B);
float minDistance(vector<Ball> &Px);

int calculationCount = 0;

int main(int argc, char ** argv){
    
    vector<Ball> list;
    clock_t time;
    
    readToArray(argv[1], list); // The file is read to the list vector
    sort(list.begin(), list.end(), compareByX); //List vector is sorted by their x
    
    time = clock();
    float smallest = minDistance(list); // Calculating the minimum distance
    time = clock() - time;
    cout << "The distance is " << smallest << endl;
    cout << "Number of total distance calculations is " << calculationCount << endl;
    cout << "Runtime is " << ( ((float)time) / CLOCKS_PER_SEC * 1000 ) << " miliseconds" << endl;
    return 0;
}

float calculateDistance(Ball& A, Ball &B){ //Calculates euclidian distance with 3 dimensions
    calculationCount++;
    float diffX = A.getX() - B.getX();
    float diffY = A.getY() - B.getY();
    float diffZ = A.getZ() - B.getZ();
    return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}

void readToArray(char* filename, vector<Ball>& list){ // Function to read the file, parse, create objects and add them to the input list
    ifstream inputFile(filename);
    string readData;
    int numberOfBalls, newX, newY, newZ;
    unsigned long intEnd;
    getline(inputFile, readData);
    if(readData[readData.size()-1] == '\n')
        readData = readData.substr(0,readData.size()-1);

    if(readData[readData.size()-1] == '\r')
       readData = readData.substr(0,readData.size()-1);

    numberOfBalls = stoi(readData);

    for(int i=0; i<numberOfBalls; i++){
        getline(inputFile, readData);
        if(readData[readData.size()-1] == '\n')
            readData = readData.substr(0,readData.size()-1);

        if(readData[readData.length()-1] == '\r')
            readData = readData.substr(0,readData.size()-1);

        intEnd = readData.find(' ', 0);
        newX = stoi(readData.substr(0, intEnd));
        readData.erase(0,intEnd+1);

        intEnd = readData.find(' ', 0);
        newY = stoi(readData.substr(0, intEnd));

        readData.erase(0,intEnd+1);

        newZ = stoi(readData);
        list.push_back(Ball(newX, newY, newZ));
    }
}

bool compareByX(const Ball& A, const Ball& B){ // Functions that compare objects in terms of their x's and y's.
    return (A.getX() < B.getX());              // These functions are used as the comparison method of std::sort()
}

bool compareByY(const Ball& A, const Ball& B){
    return (A.getY() < B.getY());
}

float minDistance(vector<Ball> &Px){ //Main min distance calculation function
    unsigned long size = Px.size();
    if(size <= 3){ // If the size is smaller than 4, find the minimum by comparing every distance
        float minDist = calculateDistance(Px[0], Px[1]);
        float distance;
        for(int i=0; i<size; i++){
            for(int j=i+1; j<size; j++){
                distance = calculateDistance(Px[i], Px[j]);
                if(distance < minDist){
                    minDist = distance;
                }
            }
        }
        return minDist;
    }

    vector<Ball> Lx,Rx;
    unsigned long midpoint = size/2;
    
    for(int i=0; i<midpoint; i++){ //Split the list sorted by X from the midpoint
        Lx.push_back(Px[i]);
    }
    for(unsigned long i=midpoint; i<size; i++){
        Rx.push_back(Px[i]);
    }

    float leftMin = minDistance(Lx); // Recursively find the minimum distance in the left side and the right side
    float rightMin = minDistance(Rx);
    float leftRightMin = (leftMin < rightMin) ? leftMin : rightMin; // Find the minimum of the minimums of two sides

    vector<Ball> s;

    for(int i=0; i<size; i++){ //From the list, add the balls which are closer to the mid yz-plane than the found minimum distance to the vector s
        float absDist = ( (Px[i].getX() - Px[midpoint].getX() < 0) ? (- Px[i].getX() + Px[midpoint].getX()) : (Px[i].getX() - Px[midpoint].getX()) );
        if( absDist < leftRightMin){
            s.push_back(Px[i]);
        }
    }

    sort(s.begin(), s.end(), compareByY); //Sort the s vector by the y coordinate
    float minDist = leftRightMin;
    float distance;

    for(int i=0; i<s.size(); i++){ // Find the minimum distance between the elements of s. It is proven that this step finishes in O(n) time
        for(int j=i+1; j<s.size() && (s[j].getY() - s[i].getY() < leftRightMin); j++){
            distance = calculateDistance(s[i], s[j]);
            if(distance < minDist){
                minDist = distance;
            }
        }
    }

    if(minDist < leftRightMin) // Return the minimum distance in the left side, right side and between sides
        return minDist;

    else if(leftMin < rightMin)
        return leftMin;

    else return rightMin;

}
