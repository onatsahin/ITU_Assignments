// BLG435E - Artificial Intelligence
// Assignment #1
// Onat Şahin - 150150129 - sahino15@itu.edu.tr

#include <iostream>
#include "PegSoltaire.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<vector<int>> start_state {{-1, -1, 1, 1, 1, -1, -1},  //Starting board state. 1 represents pegs,  and -1
                                    {-1, -1, 1, 1, 1, -1, -1},   //0 represents empty zones and -1 represents out of
                                    {1, 1, 1, 1, 1, 1, 1},       //the board.
                                    {1, 1, 1, 0, 1, 1, 1},
                                    {1, 1, 1, 1, 1, 1, 1},
                                    {-1, -1, 1, 1, 1, -1, -1},
                                    {-1, -1, 1, 1, 1, -1, -1}};
    
    Node *start_node = new Node(start_state);
    
    cout << "PERFORMING DFS..." << endl;
    vector<int> DFS_stats = DFS(start_node);
    print_stats(DFS_stats);
    
    start_node = new Node(start_state);
    
    cout << endl << endl << "PERFORMING BFS..." << endl;
    vector<int> BFS_stats = BFS(start_node);
    print_stats(BFS_stats);
    
    A_Star_Node* start_node_a = new A_Star_Node(start_state, 0);
    
    cout << endl << endl << "PERFORMING A* SEARCH WITH HEURISTIC-1 (NUMBER OF PEGS THAT CAN MAKE A MOVE)..." << endl;
    vector<int> A_star_stats = A_Star_Search(start_node_a, h1);
    print_stats(A_star_stats);
    
    A_Star_Node* start_node_a2 = new A_Star_Node(start_state, 0);
    
    cout << endl << endl << "PERFORMING A* SEARCH WITH HEURISTIC-2 (NUMBER OF POSSIBLE ACTIONS)..." << endl;
    vector<int> A_star_stats2 = A_Star_Search(start_node_a2, h2);
    print_stats(A_star_stats2);
    
    return 0;
}
