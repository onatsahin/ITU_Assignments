#include "tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void Tree::createTree(int N){
    int *array;
    array = new int[N];
    root = new node;

    for(int i=0; i<N; i++){
        array[i] = i+1;
    }
    for(int i=0; i<N; i++){
        array[i] = rand() % N + 1;
    }
    root->number = array[0];
    root->child = 1;
    minNode = array[0];

    for(int i=1; i<N; i++)
        add(root,array[i]);

    delete[] array;
}

void Tree::add(node *p, int k){
    if( !p->left ){

        p->left=new node;
        p->left->number=k;
        p->left->child=1;

        p->left->left=NULL;
        p->left->right=NULL;
    }
        else if( !p->right ){

            p->right=new node;
            p->right->number=k;
            p->right->child=1;

            p->right->left=NULL;
            p->right->right=NULL;
        }
        else if( p->left->child==p->right->child )
            add(p->left,k);
        else
            add(p->right,k);

    if( p->left && p->right ){
        p->child = 1 + p->left->child + p->right->child;
    }
    else if( p->left && !p->right ){
        p->child = 1 + p->left->child;
    }
}

void Tree::printPreorder( node *p ){

    cout << p->number << " ";

    if( p->left )
        printPreorder(p->left);
    if( p->right )
        printPreorder(p->right);
}

void Tree::printPostorder(node *p){
    if( p->left )
        printPreorder(p->left);
    if( p->right )
        printPreorder(p->right);
    cout << p->number << " ";
}

void Tree::printInorder(node *p){
    if( p->left )
        printPreorder(p->left);
    cout << p->number << " ";

    if( p->right )
        printPreorder(p->right);
}

void Tree::removeTree(node *p){
    if(p){
        if(p->left != NULL){
            removeTree(p->left);
            p->left = NULL;
        }
        if(p->right != NULL){
            removeTree(p->right);
            p->right = NULL;
        }
        delete p;
    }
}
void Tree::findMax(node *p){
    if(p){
        findMax(p->left);
        if(maxNode < p->number )maxNode = p->number;
        findMax(p->right);
    }
}
void Tree::findMin(node *p){
    if(p){
        findMin(p->left);
        if(minNode > p->number )minNode = p->number;
        findMin(p->right);
    }
}
void Tree::calculateSum(node *p){
    if(p){
        sum += p->number;
        calculateSum(p->left);
        calculateSum(p->right);
    }
}
void Tree::findNumNode(node *p){
    if(p){
        numNode++;
        findNumNode(p->left);
        findNumNode(p->right);
    }
}
float Tree::calculateAverage(node *p){
    calculateSum(p);
    findNumNode(p);
    return  (float)sum / (float)numNode;
}
void Tree::findNumLeaf(node *p){
    if(p){
        if(p->left == NULL && p->right == NULL){
            leafcount++;
        }
        findNumLeaf(p->left);
        findNumLeaf(p->right);
    }
}
int Tree::calculateDepth(){
    node *traverse = root;
    while(traverse){
        depth++;
        traverse = traverse->left;
    }
    return depth;
}

