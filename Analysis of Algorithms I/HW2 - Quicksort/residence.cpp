// Onat Şahin no: 150150129 mail: sahino15@itu.edu.tr

#include "residence.h"

Residence::Residence(int pop, int min, int max, std::string gen, int zip){
    population = pop;
    minAge = min;
    maxAge = max;
    gender = gen;
    zipCode = zip;
}

ResidenceList::ResidenceList(int N){
    std::ifstream inputFile("population_by_zip_2010.csv");
    std::string residenceData;
    std::vector<int> numbers(4);
    std::string gender;
    unsigned long dividerPos;
    
    getline(inputFile, residenceData); // The header line is read but not used in any operations.
    
    for(int i=0; i<N; i++){
        getline(inputFile, residenceData);
        
        for(int j=0; j<3; j++){     // Loop for parsing the first 3 numbers
            dividerPos = residenceData.find(',');       //Finding the first ',' character
            
            if(dividerPos == 0)     //If ',' is the first character this means the value is NULL
                numbers[j] = -1;    // -1 is given for the NULL value
            else
                numbers[j] = stoi( residenceData.substr(0, dividerPos) );   //Creating a substring and converting it to integer
            
            residenceData.erase(0, dividerPos+1);       //Erasing the first substring
        }
        
        
        dividerPos = residenceData.find(',');       //Parsing the gender as string
        
        if(dividerPos == 0)     //Checking for a NULL value for gender string
            gender = "";
        else
            gender = residenceData.substr(0, dividerPos);
        
        residenceData.erase(0, dividerPos+1);
        
        
        dividerPos = residenceData.find(',');       //Parsing zipcode as integer
        numbers[3] = stoi( residenceData.substr(0, dividerPos) );
        residenceData.erase(0, dividerPos+1);
        
        /* There is no need to keep the geoId because it is basically the same as zipcode */
        
        list.push_back( Residence(numbers[0],numbers[1],numbers[2],gender,numbers[3]) ); //Pushing to the list
    }
}

int ResidenceList::partition(int first, int last){
    int pivotPop = list[last].population;
    int pivotId = list[last].zipCode;
    int boundary = first - 1;       //This will keep the index of the last element smaller than the pivot
    
    for(int i=first; i<last; i++){
        
        if( list[i].population < pivotPop ){ // Comparing the populations and Ids and making the swap
            boundary++;
            std::iter_swap( list.begin()+boundary, list.begin()+i );
        }
        else if( list[i].population == pivotPop ){
            if( list[i].zipCode < pivotId){
                boundary++;
                std::iter_swap( list.begin()+boundary, list.begin()+i );
            }
        }       //I decided to not make the swap if the populations and ids are equal to avoid making
                //unnecessary swaps and speed up the algortihm
    }
    std::iter_swap( list.begin()+boundary+1, list.begin()+last );
    return boundary+1;      //returning the boundary
}

void ResidenceList::quickSort(int first, int last){ //Classic quicksort function
    if( first < last ){
        int pivot = partition(first, last);
        quickSort(first, pivot-1);
        quickSort(pivot+1, last);
    }
}

void ResidenceList::writeToFile(int N){ //Writing to file
    std::string line;
    std::ofstream output("output.csv");
    
    output << "population,minimum_age,maximum_age,gender,zipcode,geo_id\n";
    
    for(int i=0; i<N; i++){
        output << list[i].population << ',';
        
        if(list[i].minAge == -1)
            output << ',';
        else
            output << list[i].minAge << ',';
        
        if(list[i].maxAge == -1)
            output << ',';
        else
            output << list[i].maxAge << ',';
        
        output << list[i].gender << ',' << list[i].zipCode << ',' << "8600000US" << list[i].zipCode << '\n';
    }
    output.close();
}
