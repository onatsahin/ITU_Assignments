#include <iostream>
#include "stack.h"
#include <cstdio>
#include <ctime>
#include<cstdlib>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
using namespace std;

cell m[MAZESIZE][MAZESIZE];

void print(cell m[][MAZESIZE]);
void CreateMaze(cell m[][MAZESIZE]);
bool PathFinder(cell m[][MAZESIZE],int enterx,int entery,int camefrom);

Stack s;
int exity,exitx;
int enterx,entery;

int main()
{
    for(int i =0 ; i< MAZESIZE; i++){
        for(int j = 0; j < MAZESIZE ;j++ ){
            m[i][j] = {true,true,true,true,' ',false,i,j};
        }
    }
    system("clear");
    s.create();
    CreateMaze(m);
    print(m);
    cout << "Enter enterance point and exit points respectively: "<<endl;
    cin >> enterx >> entery;
    cin >> exitx >> exity;
    m[exitx][exity].val = 'E';
    PathFinder(m,enterx,entery,UP);
    cout << endl;
    print(m);
    s.close();
    return 0;
}

void print(cell m[][MAZESIZE])
{
    for(int i = 0; i < MAZESIZE; i++)
    {
        for(int j = 0; j < MAZESIZE; j++)
        {
            if(m[i][j].up)
                 cout << " -";
            else cout << "  ";
        }
    cout << endl;
    cout << "|";
    for(int j = 0; j < MAZESIZE; j++)
    {
        if(m[i][j].right)
            cout << m[i][j].val << "|";
        else
            cout << m[i][j].val << " ";
    }
    cout << endl;
    }
    for(int i = 0; i < MAZESIZE; i++)
    {
    if(m[MAZESIZE-1][i].down)
        cout << " -";
    }
    cout << endl;
}

void CreateMaze(cell m[][MAZESIZE]){
    bool allVisited  = false;
    /*cell *cur = m[0][1];
    cur->visited = true;*/
    int curx,cury;
    curx = 0;
    cury  = 0;
    m[0][1].visited = true;
    bool up,down,left,right;
    int randInt;
    bool corDir = false;
    cell popped;
    srand(time(NULL));
    while(!allVisited){
        left = false;up = false;down = false;right = false;
        if(!m[curx+1][cury].visited && curx + 1 < MAZESIZE)down = true;
        if(!m[curx-1][cury].visited && curx- 1 >= 0)up = true;
        if(!m[curx][cury+1].visited && cury + 1 < MAZESIZE)right = true;
        if(!m[curx][cury-1].visited && cury-1 >= 0) left= true;

        if(down || up || left || right){
          do{
            randInt = rand() % 4;
            if(randInt == 0 && down){
                s.push(m[curx][cury]);
                m[curx][cury].down = false;
                m[curx+1][cury].up = false;
                corDir = true;
                curx = curx + 1;
                m[curx][cury].visited = true;
            }
            else if(randInt == 1 && up){
                s.push(m[curx][cury]);
                m[curx][cury].up = false;
                m[curx-1][cury].down = false;
                curx = curx-1;
                m[curx][cury].visited = true;
                corDir = true;
            }
            else if(randInt == 2 && right){
                s.push(m[curx][cury]);
                m[curx][cury].right = false;
                m[curx][cury+1].left = false;
                cury = cury + 1;
                m[curx][cury].visited = true;
                corDir = true;
            }
            else if(randInt == 3 && left){
                s.push(m[curx][cury]);
                m[curx][cury].left = false;
                m[curx][cury-1].right = false;
                cury = cury - 1;
                m[curx][cury].visited = true;
                corDir = true;
            }
            }while(!corDir);
        }
        else if(!s.isempty()){
            popped = s.pop();
            curx = popped.row;
            cury = popped.colum;
        }
        else{
            curx = rand() % MAZESIZE;
            cury = rand() % MAZESIZE;
            while(!m[curx][cury].visited){
                curx = rand() % MAZESIZE;
                cury = rand() % MAZESIZE;
            }
            m[curx][cury].visited = true;
        }
        allVisited = true;
        for(int i = 0 ; i < MAZESIZE ; i++){
            for(int j = 0 ; j < MAZESIZE ; j++ ){
                if(!m[i][j].visited)allVisited = false;
            }
        }
    }
}

bool PathFinder(cell m[][MAZESIZE], int enterx, int entery, int camefrom){
    m[enterx][entery].val = 'o';
    if ( enterx == exitx && entery == exity){
        cout << "Path Found "<<endl;
        m[enterx][entery].val = 'o';
        return true;
}
    system("clear");
    print(m);
    system("sleep 0.1");
    if( enterx < MAZESIZE && !m[enterx][entery].down && camefrom != DOWN )
        if(PathFinder(m,enterx+1,entery,UP))
            return true;

    if( enterx < MAZESIZE && !m[enterx][entery].up && camefrom != UP )
        if(PathFinder(m,enterx-1,entery,DOWN))
            return true;

    if( enterx < MAZESIZE && !m[enterx][entery].right && camefrom != RIGHT )
        if(PathFinder(m,enterx,entery+1,LEFT))
            return true;

    if( enterx < MAZESIZE && !m[enterx][entery].left && camefrom != LEFT )
        if(PathFinder(m,enterx,entery-1,RIGHT))
            return true;
    m[enterx][entery].val = ' ';
    system("clear");
    print(m);
    system("sleep 0.1");
    return false;
}
