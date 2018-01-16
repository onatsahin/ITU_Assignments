// Onat Sahin No:150150129 sahino15@itu.edu.tr

#include <iostream>
#include <string>
#include <fstream>

struct Person{          //Node Struct
    std::string name;
    std::string age;
    std::string gender;
    char color;
    int num_woman;
    int num_man;
    Person *parent;
    Person *left;
    Person *right;
    
};

struct RBTree{          //Red and Black Tree Struct
    Person *root;
    void create();
    void insert(Person*);
    void RBinsert(Person*);
    bool isEmpty();
};

void RBTree::create(){ //Tree create function
    root = NULL;
};

void RBTree::insert(Person *toAdd){    //Red and black tree insertion function

    Person *traverse = root;
    bool inserted = false;
    
    if(isEmpty()){      //If empty, the person to be added is placed as root
        root = toAdd;
        return;
    }
    
    while(!inserted){   //Insertion loop
        
        if(toAdd->name < traverse->name){   //If smaller than traverse
            
            if(!traverse->left){            //If left of traverse does not exist, insert to the left
                traverse->left = toAdd;
                toAdd->parent = traverse;
                inserted = true;
            }
            else                            //If left of traverse exists, go to left
                traverse = traverse->left;
        }
        
        else if(toAdd->name > traverse->name){ //If bigger than traverse
            
            if(!traverse->right){               //If right of traverse does not exist, insert to the right
                traverse->right = toAdd;
                toAdd->parent = traverse;
                inserted = true;
            }
            else                                //If right of traverse exists, go to right
                traverse = traverse->right;
        }
    }
}

void RBTree::RBinsert(Person *toAdd){
    Person *uncle, *temp;
    insert(toAdd);
    toAdd->color = 'r';
    
    while( toAdd->parent && toAdd->parent->color=='r' ){
        if( toAdd->parent->parent->left && toAdd->parent->name == toAdd->parent->parent->left->name ){ // IF PARENT IS A LEFT CHILD
            uncle = toAdd->parent->parent->right;
            
            if(uncle && uncle->color == 'r'){
                while(toAdd->parent && toAdd->parent->parent){ //RECOLORING (CASE 1)
                    toAdd = toAdd->parent->parent;
                    toAdd->color = 'r';
                    toAdd->left->color = 'b';
                    toAdd->right->color = 'b';
                }
            }
            else{
                if(toAdd->parent->right && toAdd->name == toAdd->parent->right->name){
                    toAdd->parent->right = toAdd->left;         // LEFT ROTATE (CASE 2)
                    
                    if(toAdd->left)
                        toAdd->left->parent = toAdd->parent;
                    
                    toAdd->parent->parent->left = toAdd;
                    temp = toAdd->parent->parent;
                    toAdd->parent->parent = toAdd;
                    toAdd->left = toAdd->parent;
                    toAdd->parent = temp;
                    toAdd = toAdd->left;
                }
                toAdd->parent->color = 'b';                     //RIGHT ROTATE (CASE 3)
                toAdd->parent->parent->color = 'r';
                toAdd->parent->parent->left = toAdd->parent->right;
                
                if(toAdd->parent->right)
                    toAdd->parent->right->parent = toAdd->parent->parent;
                
                toAdd->parent->right = toAdd->parent->parent;
                toAdd->parent->parent = toAdd->parent->right->parent;
                toAdd->parent->right->parent = toAdd->parent;

                if(toAdd->parent->parent->left->name == toAdd->parent->right->name)
                    toAdd->parent->parent->left = toAdd->parent;
                else
                    toAdd->parent->parent->right = toAdd->parent;
            }
        }
        else{                                                   // IF PARENT IS A RIGHT CHILD
            uncle = toAdd->parent->parent->left;
            
            if(uncle && uncle->color == 'r'){
                while(toAdd->parent && toAdd->parent->parent){  //RECOLORING (CASE 1)
                    toAdd = toAdd->parent->parent;
                    toAdd->color = 'r';
                    toAdd->left->color = 'b';
                    toAdd->right->color = 'b';
                }
            }
            else{
                if(toAdd->parent->left && toAdd->name == toAdd->parent->left->name){
                    toAdd->parent->left = toAdd->right;         // RIGHT ROTATE (CASE 2)
                    
                    if(toAdd->right)
                        toAdd->right->parent = toAdd->parent;
                    
                    toAdd->parent->parent->right = toAdd;
                    temp = toAdd->parent->parent;
                    toAdd->parent->parent = toAdd;
                    toAdd->right = toAdd->parent;
                    toAdd->parent = temp;
                    toAdd = toAdd->right;
                }
                toAdd->parent->color = 'b';                     // LEFT ROTATE (CASE 3)
                toAdd->parent->parent->color = 'r';
                toAdd->parent->parent->right = toAdd->parent->left;
                
                if(toAdd->parent->left)
                    toAdd->parent->left->parent = toAdd->parent->parent;
                
                toAdd->parent->left = toAdd->parent->parent;
                toAdd->parent->parent = toAdd->parent->left->parent;
                toAdd->parent->left->parent = toAdd->parent;
                
                if(toAdd->parent->parent->right->name == toAdd->parent->left->name)
                    toAdd->parent->parent->right = toAdd->parent;
                else
                    toAdd->parent->parent->left = toAdd->parent;
            }
        }
    }
    root->color = 'b'; //ROOT'S COLOR IS ALWAYS BLACK
}

bool RBTree::isEmpty(){     //Returns whether the tree is empty
    return root == NULL;
}

std::string nth_woman(Person *root, int n){ //Function that finds the n th woman in a tree
    int current;
    if(root->left)                      //Setting the root's order number as current
        current = root->left->num_woman;
    else
        current = 0;
    
    if(root->gender == "F")
        current++;
    
    if(n==current && root->gender == "F")   //If n is equal to current and root is a female root is the n th woman
        return root->name;
    else if( (n==current && root->gender == "M") || n < current ) //If n is equal to current but root is a male or n is smaller than current
        return nth_woman(root->left, n);    //Call the function with the left subtree
    else
        return nth_woman(root->right, n - current); //Else, call the function with right subtree
}

std::string nth_man(Person *root, int n){ //Male version of the nth_woman function
    int current;
    if(root->left)
        current = root->left->num_man;
    else
        current = 0;
    
    if(root->gender == "M")
        current++;
    
    if(n==current && root->gender == "M")
        return root->name;
    else if( (n==current && root->gender == "F") || n < current )
        return nth_man(root->left, n);
    else
        return nth_man(root->right, n - current);
}

void countGender(Person *root){    //Sets the num_man and num_woman values
    if(root->gender == "F")         //Increase a value according to gender
        root->num_woman++;
    else
        root->num_man++;
    
    if(root->left){             //If left child exists, call the function with left child
        countGender(root->left);
        root->num_man += root->left->num_man;       //Update the values of the root according to the left child
        root->num_woman += root->left->num_woman;
    }
    if(root->right){            //Same operations with right
        countGender(root->right);
        root->num_man += root->right->num_man;
        root->num_woman += root->right->num_woman;
    }
}

void resetGenderCount(Person *root){  //Resets all num_man and num_woman values to 0
    if(!root)
        return;
    
    resetGenderCount(root->left);
    root->num_woman = 0;
    root->num_man = 0;
    resetGenderCount(root->right);
}

void printTree(Person *root, int depth){ //Print the tree with in order traversal
    if(!root)
        return;
    
    printTree(root->left, depth+1);
    
    for(int i=0; i<depth; i++)
        std::cout << '\t';
    
    if(root->parent && root->parent->left && root->name == root->parent->left->name)
        std::cout << "┌───";
    else if(root->parent && root->parent->right && root->name == root->parent->right->name)
        std::cout << "└───";
    
    std::cout << '(' << root->color << ')' << root->name << '-' << root->age << '-' << root->gender << std::endl;
    
    printTree(root->right, depth+1);
}

void deleteTree(Person *root){ //Tree deletion function
    if(root->left)
        deleteTree(root->left);
    if(root->right)
        deleteTree(root->right);
    delete root;
}

int main(int argc, const char * argv[]) {
    
    std::ifstream inputFile(argv[1]);
    std::string personData, personParsed[3];
    unsigned long dividerPos;
    RBTree tree;
    Person *newPerson;
    
    tree.create();
    
    while(getline(inputFile, personData)){ //Read the line

        if(personData[personData.size()-1] == '\r')               //Parse the line
            personData = personData.substr(0, personData.size()-1);
        
        for(int i=0; i<2; i++){
            dividerPos = personData.find('\t');
            personParsed[i] = personData.substr(0, dividerPos);
            personData.erase(0, dividerPos+1);
        }
        personParsed[2] = personData;
        
        newPerson = new Person;                 //Create new object
        newPerson->name = personParsed[0];
        newPerson->gender = personParsed[1];
        newPerson->age = personParsed[2];
        newPerson->left = NULL;
        newPerson->right = NULL;
        newPerson->parent = NULL;
        newPerson->num_man = 0;
        newPerson->num_woman = 0;
        tree.RBinsert(newPerson);               //Insert the object
        resetGenderCount(tree.root);            //Update the num_man, num_woman values
        countGender(tree.root);
    }
    printTree(tree.root, 0);                    //Print the tree
    std::cout << "3rd woman: " << nth_woman(tree.root, 3) << std::endl;
    std::cout << "4th man: " << nth_man(tree.root, 4) << std::endl;
    deleteTree(tree.root);                      //Delete the tree
    return 0;
}


