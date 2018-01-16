#include "cardmanager.h"

using namespace std;

int main(int argc, char **argv)
{
    CardManager manager(argv[3]);
    
    float time = 0;
    
    if( strcmp(argv[1], "-full") == 0 ){
        if( strcmp(argv[2], "-i") == 0 || strcmp(argv[2], "-m") == 0 ){
            time = manager.fullSort(argv[2][1]);
        }
        else{
            cout << "Invalid command" << endl;
        }
    }
    else if( strcmp(argv[1], "-filter") == 0 ){
        if( strcmp(argv[2], "-i") == 0 || strcmp(argv[2], "-m") == 0 ){
            time = manager.filterSort(argv[2][1]);
        }
        else{
            cout << "Invalid command" << endl;
        }
    }
    else{
            cout << "Invalid command" << endl;
    }
    
    std::cout << "Time elapsed: "<< time << " seconds" << std::endl;
    manager.writeToFile(argv[4]);
    return 0;
}

