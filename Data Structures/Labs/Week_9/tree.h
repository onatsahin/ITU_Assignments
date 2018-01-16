#ifndef TREE_H
#define TREE_H

struct node{
    int number, child;
    node* left;
    node* right;
};

struct Tree{
    int maxNode,minNode;
    int sum ;
    int numNode,leafcount,depth;
    node *root;
    void createTree(int);
    void removeTree(node *);
    void printPreorder(node*);
    void printInorder(node*);
    void printPostorder(node*);
    void findMax(node *);
    void findMin(node *);
    void findNumNode(node *);
    void findNumLeaf(node *);
    int calculateDepth();
    void calculateSum(node *);
    float calculateAverage(node *);
    void add(node*, int);
};

#endif // TREE_H

