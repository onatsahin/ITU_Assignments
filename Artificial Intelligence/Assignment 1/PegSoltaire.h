// BLG435E - Artificial Intelligence
// Assignment #1
// Onat Şahin - 150150129 - sahino15@itu.edu.tr

#ifndef Problem_h
#define Problem_h

#include <vector>
#include <stack>
#include <queue>
#include <ctime>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

using namespace std;

//#### NODE CLASSES #####################################################################################

class Node{     // The node for BFS and DFS
public:
    vector<vector<int>> state;
    Node(vector<vector<int>> new_state) : state(new_state) {}
};

class A_Star_Node{      // The node for A* Search
public:
    vector<vector<int>> state;
    int g_cost;     // This is the cost for coming to this node's state from the initial state
    A_Star_Node(vector<vector<int>> new_state, int g) : state(new_state), g_cost(g) {}
};

//#### FUNCTIONS THAT ARE USED IN THE SEARCH ALGORITHMS #################################################

void print_state(vector<vector<int>>& state){ // A function to print a state(board)
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(state[i][j] == -1)
                cout << "  ";
            else if(state[i][j] == 0)
                cout << "o ";
            else if(state[i][j] == 1)
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

vector<vector<int>> find_actions(vector<vector<int>>& state){ // This function finds all possible actions that can
    vector<vector<int>> new_state;                            // be performed from the input state
    vector<vector<int>> actions;
    vector<int> new_action(3); // Format : {row of peg, column of peg, direction to move}
    
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(state[i][j] != 1)
                continue;  // Continue if not a peg
            
            new_action[0] = i; // For pegs, it checks surrounding zones to find possible actions.
            new_action[1] = j; // If an action is found, creates an action vector and pushes it to actions vector.
            
            if(j > 1 && state[i][j-1] == 1 && state[i][j-2] == 0){
                new_action[2] = LEFT;
                actions.push_back(new_action);
            }
            if(i > 1 && state[i-1][j] == 1 && state[i-2][j] == 0){
                new_action[2] = UP;
                actions.push_back(new_action);
            }
            if(j < 5 && state[i][j+1] == 1 && state[i][j+2] == 0){
                new_action[2] = RIGHT;
                actions.push_back(new_action);
            }
            if(i < 5 && state[i+1][j] == 1 && state[i+2][j] == 0){
                new_action[2] = DOWN;
                actions.push_back(new_action);
            }
        }
    }
    
    return actions;
}

vector<vector<int>> perform_action(vector<vector<int>>& state, vector<int>& action){
    vector<vector<int>> new_state; // Given a state and an action, this function changes the state according to the action.
    int i = action[0];
    int j = action[1];
    int direction = action[2];
    
    new_state = state;
    
    if(direction == LEFT){
        new_state[i][j] = 0;
        new_state[i][j-1] = 0;
        new_state[i][j-2] = 1;
    }
    else if (direction == UP){
        new_state[i][j] = 0;
        new_state[i-1][j] = 0;
        new_state[i-2][j] = 1;
    }
    else if (direction == RIGHT){
        new_state[i][j] = 0;
        new_state[i][j+1] = 0;
        new_state[i][j+2] = 1;
    }
    else if (direction == DOWN){
        new_state[i][j] = 0;
        new_state[i+1][j] = 0;
        new_state[i+2][j] = 1;
    }
    
    return new_state;
}

//#### BFS AND DFS FUNCTIONS ###########################################################################

vector<int> BFS(Node *start_node){
    bool goal_found = false;
    Node *current_node, *new_node, *to_delete;
    vector<vector<int>> current_state, possible_actions;
    unsigned long number_of_actions, max_node_in_mem = 0;
    int generated_node_count = 1, expanded_node_count = 0, number_of_pegs = 0;
    vector<int> results(4);
    clock_t runtime;
    
    runtime = clock(); //Start the clock
    
    queue<Node*> q;
    q.push(start_node); //Add starting node to the queue
    
    while(!goal_found){ // Classic BFS Algorithm that also records stats like expanded node count and generated node count
        current_node = q.front(); // Pop a node from the queue and extract its state
        current_state = current_node->state;
        q.pop();
        delete current_node;
        
        possible_actions = find_actions(current_state); // Child states are found with find_actions function
        number_of_actions = possible_actions.size();
        
        if(number_of_actions == 0) //If no child state is found, this is a goal state
            goal_found = true;
        else{
            expanded_node_count++;
            generated_node_count += number_of_actions;
        }
        
        for(int i=0; i<number_of_actions; i++){ // Generate the child states with perform_action function, create a node with the child state and push it to the queue
            new_node = new Node(perform_action(current_state, possible_actions[i]));
            q.push(new_node);
        }
        if(q.size() > max_node_in_mem)
            max_node_in_mem = q.size();
        
    }
    
    runtime = clock() - runtime;
    
    cout << "Found Goal State:" << endl << endl;
    print_state(current_state);
    cout << "The running time: " << (float)runtime / CLOCKS_PER_SEC << " seconds" << endl;
    
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(current_state[i][j] == 1)
                number_of_pegs++;
        }
    }
    
    while(!q.empty()){ // Empty the queue and deallocate memory
        to_delete = q.front();
        q.pop();
        delete to_delete;
    }
    
    results[0] = generated_node_count; // Fill results vector with stats
    results[1] = expanded_node_count;
    results[2] = (int) max_node_in_mem;
    results[3] = number_of_pegs;
    
    return results;
}

vector<int> DFS(Node *start_node){ // Classic DFS algorithm adapted for this problem. Only difference from BFS is
    bool goal_found = false;        // that a stack is used instead of a queue.
    Node *current_node, *new_node, *to_delete;
    vector<vector<int>> current_state, possible_actions;
    unsigned long number_of_actions, max_node_in_mem = 0;
    int generated_node_count = 1, expanded_node_count = 0, number_of_pegs = 0;
    vector<int> results(4);
    clock_t runtime;
    
    runtime = clock();
    
    stack<Node*> s;
    s.push(start_node);
    
    while(!goal_found){
        current_node = s.top();
        current_state = current_node->state;
        s.pop();
        delete current_node;
        
        possible_actions = find_actions(current_state);
        number_of_actions = possible_actions.size();
        
        if(number_of_actions == 0)
            goal_found = true;
        else{
            expanded_node_count++;
            generated_node_count += number_of_actions;
        }
        
        for(int i=0; i<number_of_actions; i++){
            new_node = new Node(perform_action(current_state, possible_actions[i]));
            s.push(new_node);
        }

        if(s.size() > max_node_in_mem)
            max_node_in_mem = s.size();
    }
    
    runtime = clock() - runtime;
    
    cout << "Found Goal State:" << endl << endl;
    print_state(current_state);
    cout << "The running time: " << (float)runtime / CLOCKS_PER_SEC << " seconds" << endl;
    
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(current_state[i][j] == 1)
                number_of_pegs++;
        }
    }
    
    while(!s.empty()){
        to_delete = s.top();
        s.pop();
        delete to_delete;
    }
    
    results[0] = generated_node_count;
    results[1] = expanded_node_count;
    results[2] = (int) max_node_in_mem;
    results[3] = number_of_pegs;
    
    return results;
}

//#### A* SEARCH ALGORITHM AND RELATED FUNCTIONS ###################################################################

int h1(vector<vector<int>>& state){ // First heuristic function to use with A* Search
    int movable_peg_count = 0;      // This function returns the number of pegs that can make a move
    
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(state[i][j] != 1)
                continue;
            
            if(j > 1 && state[i][j-1] == 1 && state[i][j-2] == 0){
                movable_peg_count++;
            }
            else if(i > 1 && state[i-1][j] == 1 && state[i-2][j] == 0){
                movable_peg_count++;
            }
            else if(j < 5 && state[i][j+1] == 1 && state[i][j+2] == 0){
                movable_peg_count++;
            }
            else if(i < 5 && state[i+1][j] == 1 && state[i+2][j] == 0){
                movable_peg_count++;
            }
        }
    }
    return movable_peg_count;
}

int h2(vector<vector<int>>& state){ // Second heuristic function to use with A* Search
    return (int)find_actions(state).size(); // This function returns the number of possible actions from the current state
}


int find_frontier_min_index( vector< pair<int, A_Star_Node*> >& frontier ){
    unsigned long frontier_size = frontier.size(); // This is a min function to find the node in the frontier with
    long long int min_cost = 10E9-1;               // the min g + h cost
    int min_index = -1;
    
    for(int i=0; i<frontier_size; i++){
        if(frontier[i].first < min_cost){
            min_cost = frontier[i].first;
            min_index = i;
        }
    }
    return min_index;
}

vector<int> A_Star_Search(A_Star_Node *start_node, int h(vector<vector<int>>& state)){
    bool goal_found = false;
    A_Star_Node *current_node, *new_node;
    vector<vector<int>> current_state, possible_actions;
    unsigned long number_of_actions, max_node_in_mem = 0;
    int generated_node_count = 1, expanded_node_count = 0, number_of_pegs = 0, current_node_index, current_g_cost;
    vector<int> results(4);
    clock_t runtime;
    
    runtime = clock();
    
    vector< pair<int, A_Star_Node*> > frontier; // Create frontier pair vector. Pair format: g + h cost, Node
    frontier.push_back( make_pair( h(start_node->state), start_node ) ); //For initial node, g cost is 0.
                                                                        // Create a pair for the initial state and add it to the frontier.
    while(!goal_found){
        current_node_index = find_frontier_min_index(frontier); // Find the node with minimum g + h cost in frontier
        current_node = frontier[current_node_index].second;   // Extract its contents
        current_state = current_node->state;
        current_g_cost = current_node->g_cost;
        
        frontier.erase(frontier.begin() + current_node_index); // Erase that expanded node from the frontier.
        delete current_node;
        possible_actions = find_actions(current_state); // Find child states
        number_of_actions = possible_actions.size();
        
        if(number_of_actions == 0)
            goal_found = true;
        else{
            expanded_node_count++;
            generated_node_count += number_of_actions;
        }
        
        for(int i=0; i<number_of_actions; i++){ // Add child states to the frontier with their g + h costs.
            new_node = new A_Star_Node(perform_action(current_state, possible_actions[i]), current_g_cost+1);
            frontier.push_back( make_pair( new_node->g_cost + h(new_node->state), new_node ) );
        }
        if(frontier.size() > max_node_in_mem)
            max_node_in_mem = frontier.size();
    }
    
    runtime = clock() - runtime;
    
    cout << "Found Goal State:" << endl << endl;
    print_state(current_state);
    cout << "The running time: " << (float)runtime / CLOCKS_PER_SEC << " seconds" << endl;
    
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(current_state[i][j] == 1)
                number_of_pegs++;
        }
    }
    
    for(int i=0; i<frontier.size(); i++){
        delete frontier[i].second;
    }
    
    results[0] = generated_node_count;
    results[1] = expanded_node_count;
    results[2] = (int) max_node_in_mem;
    results[3] = number_of_pegs;
    
    return results;
}

void print_stats(vector<int>& stats){
    cout << "The number of nodes generated: " << stats[0] << endl;
    cout << "The number of nodes expanded: " << stats[1] << endl;
    cout << "The maximum number of nodes kept in the memory: " << stats[2] << endl;
    cout << "The number of pegs in the found final state: " << stats[3] << endl;
}
#endif /* Problem_h */
