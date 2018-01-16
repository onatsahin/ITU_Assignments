// Onat Şahin no: 150150129 mail: sahino15@itu.edu.tr

#ifndef residence_h
#define residence_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <ctime>

class Residence{
    friend class ResidenceList;
    int population;
    int minAge;
    int maxAge;
    std::string gender;
    int zipCode;
    /* There is no need to keep the geoId because it is basically the same as zipcode */
public:
    Residence(int,int,int,std::string,int);
};

class ResidenceList{
    std::vector<Residence> list;
    int partition(int,int);
public:
    ResidenceList(int);
    void quickSort(int,int);
    void writeToFile(int);
};


#endif /* residence_h */
