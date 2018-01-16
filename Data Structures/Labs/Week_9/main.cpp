#include <iostream>
#include "tree.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int N;
    cout << "Enter N: ";
    cin >> N;
    srand(time(NULL));
    Tree tree;
    tree.createTree(N);
    tree.maxNode = 0;
    tree.numNode = 0;
    tree.sum = 0;
    tree.leafcount = 0;
    tree.depth = 0;

    tree.printPreorder(tree.root);
    cout << endl;
    tree.printInorder(tree.root);
    cout << endl;
    tree.printPostorder(tree.root);
    tree.findMax(tree.root);
    tree.findMin(tree.root);
    tree.calculateSum(tree.root);
    tree.findNumNode(tree.root);
    tree.findNumLeaf(tree.root);
    cout << endl<<endl;
    cout <<"Max: " <<tree.maxNode << endl<<endl;
    cout <<"Min: "<< tree.minNode<< endl<<endl;
    cout <<"Sum: "<<tree.sum<<endl<<endl;
    cout <<"Number of Node: "<<tree.numNode<<endl<<endl;
    cout << "Average: "<<tree.calculateAverage(tree.root)<<endl<<endl;
    cout << "Leaf count: "<<tree.leafcount<<endl<<endl;
    cout << "Depth: "<<tree.calculateDepth()<<endl<<endl;
    tree.removeTree(tree.root);
    return 0;
}

