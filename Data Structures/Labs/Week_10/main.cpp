#include "data.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    int N;
    int find;
    cout << "Enter N: ";
    cin >> N;
    cout << "What to find: ";
    cin >> find;
    srand(time(NULL));
    Tree tree;
    tree.createTree(N);
    tree.Inorderfound = 0;
    cout << endl;
    cout << "BFS is runing..." <<endl;
    cout << "BFS: " << tree.BFS(find) << " steps."<<endl<<endl;
    cout << "DFS is runing..." <<endl;
    cout << "DFS: " << tree.DFS(find) << " steps."<<endl<<endl;
    cout << "Inorder is runing..."<<endl;
    tree.InorderSearch(tree.root,find);
    if(tree.Inorderfound == 0)
        cout << "Could not find"<<endl;
    tree.removeTree(tree.root);

    return 0;

}

