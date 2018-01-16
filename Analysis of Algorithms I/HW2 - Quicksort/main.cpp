// Onat Şahin no: 150150129 mail: sahino15@itu.edu.tr

#include "residence.h"

int main(int argc, const char * argv[]) {
    int N = atoi(argv[1]);
    clock_t begin = 0, end = 0;
    
    ResidenceList list(N); //Creating the list
    
    begin = clock();
    list.quickSort(0, N-1); //Launching quicksort while recording the time
    end = clock();
    
    std::cout << "Time elapsed: " << ( (float)(end - begin) )/CLOCKS_PER_SEC * 1000 << " miliseconds" << std::endl;
    
    list.writeToFile(N);
    
    return 0;
}
