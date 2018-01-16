#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "stack.h"
#include <unistd.h>
using namespace std;

char Maze[14][23] = {
"#o###################",
"#     #      #    # #",
"# ### # ###### ## # #",
"# # #        # #  # #",
"# # ### ######## ## #",
"#     # # ##   #    #",
"### # # # ## # # ####",
"# # # # #    #      #",
"# # # # # ######### #",
"# # # # # #       # #",
"# # #   # # #####   #",
"# # ##### # #   #####",
"#         #   #     #",
"###################E#" };

void printlab(char l[14][23]) {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 23; j++)
        cout << l[i][j];
        cout << endl;
    }
    cout << endl;
}

int main(){
    cout << endl;
    printlab(Maze);
    Stack s;
    Stack moves;
	Stack decision;
	decision.create();
    moves.create();
    s.create();
    position entrance = {0,1,0,0,0,0,0};
    position exit = {13,21,0,0,0,0,0};
    position p = entrance;
    p.camefrom = UP;
    bool goback = false;
    while(p.x != exit.x || p.y != exit.y){
        Maze[p.x][p.y] = 'o';
        moves.push(p);//Record every move.
        system ("sleep 0.1");
        system("clear");
        printlab(Maze);
        cout << p.x << " "<<p.y<<endl;
		cout << endl;
        if(!goback){
            p.right = 0;
            p.left = 0;
            p.up = 0;
            p.down = 0;
            if(p.x < 14 && Maze[p.x+1][p.y] != '#')p.down = 1;
            if(p.x > 0 && Maze[p.x-1][p.y] != '#' )p.up = 1;
            if(p.y < 23 && Maze[p.x][p.y+1] != '#')p.right = 1;
            if(p.y > 0  && Maze[p.x][p.y-1] != '#')p.left = 1;
        }
        else goback = false;
        bool moved = true;
        position past = p;

        if(p.left && p.camefrom != LEFT && (Maze[p.x][p.y-1] != 'o')){
            p.y--;
            p.camefrom = RIGHT;
            past.left = 0 ;
        }
        else if(p.down && p.camefrom != DOWN && Maze[p.x+1][p.y] != 'o'){
            p.x++;
            p.camefrom = UP;
            past.down = 0;
        }
		else if(p.right && p.camefrom != RIGHT  && Maze[p.x][p.y+1] != 'o'){
            p.y++;
            p.camefrom = LEFT;
            past.right = 0 ;
        }

        else if(p.up && p.camefrom != UP && Maze[p.x-1][p.y] != 'o'){
            p.x--;
            p.camefrom = DOWN;
            past.up = 0 ;
        }


        else moved = false;

        if(p.x != exit.x || p.y != exit.y){
            if( (p.up + p.down + p.left + p.right) > 2 ){
                s.push(past);
				decision.push(past);
            }

            if (!moved){
                if(!s.isempty()){
                    position temp = p;
                    p = s.pop();
                    goback = true;
					while(temp.x != p.x || temp.y != p.y){
                        Maze[temp.x][temp.y] = ' ';
                        temp = moves.pop();
                    }
                }
				else {
					p = decision.pop();
					goback = true;
				}
            }
        }
    }
    cout << "PATH FOUND"<<endl;
    int i=1;
    position temp;
    while(!moves.isempty()){//Print the path.
         temp = moves.pop();
        cout << i<<". "<< temp.x << ","<<temp.y <<"--> ";
        i++;
    }
    s.close();
    moves.close();

/*	char Maze2[14][23] = {
	"#o###################",
	"#     #           # #",
	"# # # # ###### ## # #",
	"# # #        # #  # #",
	"# # ### ### #### ## #",
	"#   # # # ##   #    #",
	"### # # # ## # # ####",
	"# # # # #    #      #",
	"# # # # # # ####### #",
	"# # # # # #       # #",
	"# # #   # # #####   #",
	"# # # ### # #   #####",
	"#         #   #     #",
	"#####################" };
	printlab(Maze2);
	cout << endl;
    p = entrance;
    p.camefrom = UP;
    goback = false;
	bool cont = true;
	int cycle = 0;
	    while(cont){
        Maze2[p.x][p.y] = 'o';
        system ("sleep 0.1");
        system("clear");
        printlab(Maze2);
		cout << endl;
		cout << endl;
        if(!goback){
			if(Maze2[p.x][p.y-1] == 'o' && p.camefrom != LEFT )cycle++;
			if(Maze2[p.x+1][p.y] == 'o' && p.camefrom != DOWN )cycle++;
			if(Maze2[p.x-1][p.y] == 'o' && p.camefrom != UP )cycle++;
			if(Maze2[p.x][p.y+1] == 'o' && p.camefrom != RIGHT )cycle++;
		}
		if(!goback){
            p.right = 0;
            p.left = 0;
            p.up = 0;
            p.down = 0;
            if(p.x < 14 && Maze2[p.x+1][p.y] != '#')p.down = 1;
            if(p.x > 0 && Maze2[p.x-1][p.y] != '#' )p.up = 1;
            if(p.y < 23 && Maze2[p.x][p.y+1] != '#')p.right = 1;
            if(p.y > 0  && Maze2[p.x][p.y-1] != '#')p.left = 1;
        }
        else goback = false;
        bool moved = true;
        position past = p;

        if(p.left && p.camefrom != LEFT && (Maze2[p.x][p.y-1] != 'o')){
            p.y--;
            p.camefrom = RIGHT;
            past.left = 0 ;
        }
		 else if(p.up && p.camefrom != UP && Maze2[p.x-1][p.y] != 'o'){
            p.x--;
            p.camefrom = DOWN;
            past.up = 0 ;
        }
		else if(p.down && p.camefrom != DOWN && Maze2[p.x+1][p.y] != 'o'){
            p.x++;
            p.camefrom = UP;
            past.down = 0;
        }

        else if(p.right && p.camefrom != RIGHT  && Maze2[p.x][p.y+1] != 'o'){
            p.y++;
            p.camefrom = LEFT;
            past.right = 0 ;
        }

        else moved = false;

        if(cont){
            if( (p.up + p.down + p.left + p.right) > 2 ){
				s.push(past);
				decision.push(past);
            }

            if (!moved){
                if(!s.isempty()){
                    position temp = p;
                    p = s.pop();
                    goback = true;
                }
            }
        }
		cont = false;
		for(int i = 0 ; i < 14 ; i++){
			for(int j = 0; j < 23 ; j++ ){
				if(Maze2[i][j] == ' '){
					cont = true;
				}
			}
		}
    }

	cout << "Cycle: 	"<< cycle << endl;
    decision.close();*/
    return 0;
}
