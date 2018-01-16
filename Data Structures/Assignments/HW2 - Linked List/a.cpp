#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main(){
    FILE *file;
    file = fopen("songbook.txt", "r+");

    char name[50];

    fseek(file, 0, SEEK_SET);
    for(int i=0; i<23; i++){
        fscanf(file, "%[^\t]s", name);
        cout << name << "control"<< endl;
        fseek(file, 1, SEEK_CUR);

        fscanf(file, "%[^\t]s", name);
        cout << name <<"control"<<  endl;
        fseek(file, 1, SEEK_CUR);

        fscanf(file, "%[^\t]s", name);
        cout << name <<"control"<<  endl;
        fseek(file, 1, SEEK_CUR);

        fscanf(file, "%[^\r]s", name);
        cout << name <<"control"<<  endl;
        fseek(file, 2, SEEK_CUR);
    }


    /*fscanf(file, "%[^\t]s", name);
    cout << name <<"control"<<  endl;*/

    fclose(file);
    return 0;
}
