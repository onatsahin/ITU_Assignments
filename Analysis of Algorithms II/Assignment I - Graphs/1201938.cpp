//Name: Onat Şahin   No: 150150129
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

class State{ //State class that keeps info on who is on which side
public:
    char locations[4]; // 0-farmer, 1-rabbit, 2-carrot, 3-fox
    State(char f, char r, char c, char fo);
    State(){}
};

State::State(char f, char r, char c, char fo){
    locations[0] = f;
    locations[1] = r;
    locations[2] = c;
    locations[3] = fo;
}

void initializeStates(vector<State>& arr);
void connectStates(vector< vector<int> > &adj, vector<State>& nodes);
bool isConnected(State& a, State& b);
bool isValid(int state);
int bfs(vector< vector<int> > &adj, vector<State>& nodes, vector<bool>& visited, vector<int>& prev);
int dfs(vector< vector<int> > &adj, vector<State>& nodes, vector<bool>& visited, vector<int>& prev);
void printSolution(vector<int>& previous, vector<State>& nodes);
void printState(State& state);
void printAction(State& previous, State& current);


int main(int argc, const char * argv[]){
    int visitedCount, nodeInMemory=0, current;
    unsigned long begin,end;
    vector<State> states;
    initializeStates(states); //initialize the states
    
    int stateNum = (int)states.size();
    vector<bool> visited(stateNum, false);
    vector<int> previous(stateNum, -1);
    vector< vector<int> > adjacency(stateNum, vector<int>(stateNum)); // create adjacency matrix
    connectStates(adjacency, states); //connect the states
    
    if(argv[1][0] == 'd'){   //execute the selected algortihm
        cout << "Algorithm: DFS" << endl;
        begin = clock();
        visitedCount = dfs(adjacency, states, visited, previous);
        end = clock();
    }
    else{
        cout << "Algorithm: BFS" << endl;
        begin = clock();
        visitedCount = bfs(adjacency, states, visited, previous);
        end = clock();
    }
    
    // Print the results
    
    cout << "Number of visited nodes: " << visitedCount << endl;
    
    current = stateNum-1;
    do{
        current = previous[current];
        nodeInMemory++;
    }while(current != -1);
    cout << "Maximum number of nodes kept in the memory: " << nodeInMemory << endl;
    cout << "Running time: " << ( (float)(end - begin) )/CLOCKS_PER_SEC * 1000 << " miliseconds" << endl;
    cout << "Solution move count: " << nodeInMemory-1 << endl;
    printSolution(previous, states);

    return 0;
}

void initializeStates(vector<State>& arr){
    string toPermute = "llllrrrr"; // The function permutes this string and takes the first 4 characters.
    string prevInstance;           // If that permutation has not been converted to a state, it is converted and added to the vector.
    
    do{
        if(toPermute != "rrrrllll" && toPermute.substr(0,4) != prevInstance)
            arr.push_back(State(toPermute[0],toPermute[1],toPermute[2],toPermute[3]));
        
        prevInstance = toPermute.substr(0,4);
    }while(next_permutation(toPermute.begin(), toPermute.end()));
    
    arr.push_back(State('r','r','r','r'));
}

void connectStates(vector< vector<int> > &adj, vector<State>& nodes){
    for(int i=0; i<nodes.size(); i++){      //This function traverses sets up the adjacency matrix by traversing it and
        for(int j=i; j<nodes.size(); j++){  //checking if it is possible to move to traversed state from the current state
            if(isConnected(nodes[i], nodes[j])){
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
            else{
                adj[i][j] = 0;
                adj[j][i] = 0;
            }
        }
    }
}

bool isConnected(State& a, State& b){ //Checks if it is possible to move to state b from state a by checking the
    if(a.locations[0] != b.locations[0]){ //location data in that state
        int count = 0;
        for(int i=1; i<4; i++){
            if(a.locations[i] != b.locations[i])
                count++;
        }
        if(count <= 1)
            return true;
    }
    return false;
}

int bfs(vector< vector<int> > &adj, vector<State>& nodes, vector<bool>& visited, vector<int>& prev){
    queue<int> q;           //Classic bfs algorithm. Additionally, it keeps the previous nodes and counts visited nodes.
    int visitedCount = 0;   //Also, if a state is invalid, the algorithm returns from that route
    q.push(0);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        if(!visited[current]){
            visited[current] = true;
            visitedCount++;
            if(current == nodes.size()-1)
                return visitedCount;
            if(((nodes[current].locations[1] == nodes[current].locations[2]) && (nodes[current].locations[0] != nodes[current].locations[1])) || ((nodes[current].locations[1] == nodes[current].locations[3]) && (nodes[current].locations[0] != nodes[current].locations[1])))
                continue;
            for(int i = 0; i<nodes.size(); i++){
                if(adj[current][i] == 1 && !visited[i]){
                    prev[i] = current;
                    q.push(i);
                }
            }
        }
    }
    return visitedCount;
}

int dfs(vector< vector<int> > &adj, vector<State>& nodes, vector<bool>& visited, vector<int>& prev){
    stack<int> s;           //Classic dfs algorithm. Additionally, it keeps the previous nodes and counts visited nodes.
    int visitedCount = 0;   //Also, if a state is invalid, the algorithm returns from that route
    s.push(0);
    while(!s.empty()){
        int current = s.top();
        s.pop();
        if(!visited[current]){
            visited[current] = true;
            visitedCount++;
            if(current == nodes.size()-1)
                return visitedCount;
            if(((nodes[current].locations[1] == nodes[current].locations[2]) && (nodes[current].locations[0] != nodes[current].locations[1])) || ((nodes[current].locations[1] == nodes[current].locations[3]) && (nodes[current].locations[0] != nodes[current].locations[1])))
                continue;
            for(int i = 0; i<nodes.size(); i++){
                if(adj[current][i] == 1 && !visited[i]){
                    prev[i] = current;
                    s.push(i);
                }
            }
        }
    }
    return visitedCount;
}

void printSolution(vector<int>& previous, vector<State>& nodes){ //Main print function
    stack<int> states;
    int current = (int)nodes.size()-1; //Backtraces the previous vector and pushes each element to a stack to get the route
    int prevState;
    
    do{
        states.push(current);
        current = previous[current];
    }while(current != -1);
    
    current = states.top();
    states.pop();
    printState(nodes[current]);
    prevState = current;
    
    while(!states.empty()){
        current = states.top();
        printAction(nodes[prevState], nodes[current]);
        printState(nodes[current]);
        prevState = current;
        states.pop();
    }
}

void printState(State& state){ //Prints state objects
    for(int i=0; i<4; i++){
        if(state.locations[i] == 'l'){
           if(i==0)
               cout << "Farmer ";
           else if(i==1)
               cout << "Rabbit ";
           else if(i==2)
               cout << "Carrot ";
           else if(i==3)
               cout << "Fox ";
        }
    }
    cout << "|| ";
    for(int i=0; i<4; i++){
        if(state.locations[i] == 'r'){
            if(i==0)
                cout << "Farmer ";
            else if(i==1)
                cout << "Rabbit ";
            else if(i==2)
                cout << "Carrot ";
            else if(i==3)
                cout << "Fox ";
        }
    }
    cout << endl;
}

void printAction(State& previous, State& current){ // Prints transitions between states
    cout << "(Farmer, ";
    if(current.locations[0] == 'l'){
        for(int i=1; i<4; i++){
            if(previous.locations[i] == 'r' && current.locations[i] == 'l'){
                if(i==1)
                    cout << "Rabbit, ";
                else if(i==2)
                    cout << "Carrot, ";
                else if(i==3)
                    cout << "Fox, ";
                break;
            }
        }
        cout << "< )" << endl;
    }
    else{
        for(int i=1; i<4; i++){
            if(previous.locations[i] == 'l' && current.locations[i] == 'r'){
                if(i==1)
                    cout << "Rabbit, ";
                else if(i==2)
                    cout << "Carrot, ";
                else if(i==3)
                    cout << "Fox, ";
                break;
            }
        }
        cout << "> )" << endl;
    }
}














