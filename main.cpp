#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <limits>

using namespace std;

string getCityFromString(string line) {
    string cleanedString = line.substr(7);
    return cleanedString;
}

unordered_map<string, vector<string>> readFile() {
    string line;
    ifstream flightDirectory("flight.txt");

    //unordered map acts as a key value pairs, with the key being the FROM country and the value being a vector of the destination countries
    unordered_map<string, vector<string>> map;
    bool isFrom;
    vector<string> toCities, fromCities;
    vector<vector<string>> allToCities;
    string toCity, fromCity;

    //Gets all of the destinations and puts them in their respective vectors
    if (flightDirectory.is_open()) {
        while (getline(flightDirectory, line)) {
            string city = getCityFromString(line);

            if (line.at(0) == 'F') {
                fromCities.push_back(city);
                if (!toCities.empty()) {
                    allToCities.push_back(toCities);
                }
                toCities.clear();
            } else {
                toCities.push_back(city);
            }
        }

        allToCities.push_back(toCities);
        flightDirectory.close();
    } else {
        cout << "file is closed";
    }

    //converts the vectors into a hashmap
    for (int i = 0; i < fromCities.size(); i++) {
        map[fromCities[i]] = allToCities[i];
    }
    return map;
}

vector<vector<int>> toAdjacencyList(unordered_map<string, vector<string>> map, vector<string> indexToCity ) {
    int size = indexToCity.size();
    vector<vector<int>> adjacencyList(size);

    for(int i = 0 ; i < size ; i++) {
        for(string fromCity : map[indexToCity[i]]) {
            for(int j = 0 ; j < size ; j++) {
                if(indexToCity[j] == fromCity) {
                    adjacencyList[i].push_back(j);
                    break;
                }
            }
        }
    }
    return adjacencyList;
}

void printCities(unordered_map<string, vector<string>> map){
    int i = 0;
    for (pair<string, vector<string>> pair : map) {
        cout << i++ << " - From: " << pair.first << endl;
    }
}

//Q1: Shortest path A to B in X connections: Ben Grider & Nhu Pham)
void functionOne(vector<vector<int>> adjacencyList, int from, int to, int maxConnections, vector<string> indexToCity) {
    queue<int> q; 
    vector<int> distance(adjacencyList.size(), -1);
    vector<int> parent(adjacencyList.size(), -1);
    bool found = false;

    //start is finish
    if(from == to) {
        cout << "Already at Location: 0 flights to - " << indexToCity[from] << endl;
        return;
    }

    //set the first node in queue to be the from node and set that distance to 0
    q.push(from);
    distance[from] = 0;


    //While the queue is not empty and the connections is not found
    while(!q.empty() && !found) {

        //set the curr node from the starting node and pop the from node out
        int curr = q.front();
        q.pop();

        //if we are within our connection, continue
        if(distance[curr] < maxConnections) {

            //for each neighbor in adjacency list
            for(int neighbor : adjacencyList[curr]) {

                //if not visited, visit
                if(distance[neighbor] == -1) {
                    distance[neighbor] = distance[curr] + 1;
                    parent[neighbor] = curr;
                    q.push(neighbor);

                    //if found, break
                    if(neighbor == to) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    //node not found at all (if max connections is too high)
    if(!found || distance[to] == -1) {
        cout << "No route exists" << endl;
        return;
    }

    //node not in within allowed connections
    else if(distance[to] > maxConnections) {
        cout << "No route within " << maxConnections << " flights" << endl;
        return;
    }

    //print final route and return to main()
    vector<int> finalRoute;
    for(int i = to ; i != -1 ; i = parent[i]) {
        finalRoute.push_back(i);
    }

    int flightsUsed = distance[to];
    int connectionsUsed = flightsUsed - 1;
    cout << "The route from " << indexToCity[from] << " to " << indexToCity[to] << " is " << endl;
    for(int i = finalRoute.size() - 1 ; i>=0 ; i--) {
        cout << indexToCity[finalRoute[i]];
        if(i > 0) { cout << " | "; }
    }
    cout << endl << "Smallest number of connections: " << connectionsUsed << endl << endl;
    return;

}

//Q2: Shortest Path A to B through C and D: Alan Ortega
void functionTwo(vector<vector<int>> adjacencyList, int from, int to, int connectOne, int connectTwo, vector<string> indexToCity) {

}

//Q3: Shortest Round Trip: Ben Grider
void functionThree(vector<vector<int>>& adjacencyList, int startingCity, vector<string>& indexToCity) {
    queue<int> q; 
    int size = adjacencyList.size();
    vector<int> parent(size, -1);
    vector<bool> visited(size, false);
    bool found = false;
    int lastCity = -1;

    visited[startingCity] = true;

    //set the first node in queue to be the from node and set that distance to 0
    q.push(startingCity);


    //While the queue is not empty and the connections is not found
    while(!q.empty() && !found) {

        //set the curr node from the starting node and pop the from node out
        int curr = q.front();
        q.pop();

        //for each neighbor in adjacency list
        for(int neighbor : adjacencyList[curr]) {

            //if found, break
            if(neighbor == startingCity && curr != startingCity) {
                found = true;
                lastCity = curr;
                break;
            }
            //if not visited, visit
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    //node not found at all 
    if(!found) {
        cout << "No route exists" << endl;
        return;
    }

    vector<int> reverseRoute;
    for(int i = lastCity ; i != -1 ; i = parent[i]) {
        reverseRoute.push_back(i);
    }
    vector<int> finalRoute;
    
    int RRSize = reverseRoute.size() - 1;
    for(int i = RRSize ; i >= 0 ; i--) {
        finalRoute.push_back(reverseRoute[i]);
    }
    finalRoute.push_back(startingCity);
    //print final route and return to main()
    cout << endl << "----------------------------------------------------------------------" << endl;
    cout << endl << "The shortest round trip starting at " << indexToCity[startingCity] <<  " is "<< endl;
    for(int i = finalRoute.size() - 1 ; i>=0 ; i--) {
        cout << indexToCity[finalRoute[i]];
        if(i > 0) { cout << " | "; }
    }
    cout << endl << "----------------------------------------------------------------------" << endl;
    return;

}

//Q4: Best meeting city: Nhu Pham
void functionFour(vector<vector<int>>& adjacencyList, vector<string>& indexToCity, int A, int B, int C) {
    int n = (int)adjacencyList.size();

    // dist[k][u] and parent[k][u] for sources k=0..2 => A,B,C
    int src[3] = {A,B,C};
    vector<vector<int>> dist(3, vector<int>(n, -1));
    vector<vector<int>> parent(3, vector<int>(n, -1));

    auto bfs = [&](int k){
        queue<int> q;
        int s = src[k];
        dist[k][s] = 0;
        q.push(s);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : adjacencyList[u]){
                if(dist[k][v] == -1){
                    dist[k][v] = dist[k][u] + 1;
                    parent[k][v] = u;
                    q.push(v);
                }
            }
        }
    };

    // run BFS from A, B, C
    for(int k=0;k<3;k++) bfs(k);

    // choose meeting city with min sum of hops (exclude A/B/C)
    int meet = -1;
    int best = numeric_limits<int>::max();
    for(int u=0; u<n; ++u){
        if(u==A || u==B || u==C) continue;
        if(dist[0][u]==-1 || dist[1][u]==-1 || dist[2][u]==-1) continue; // someone can't reach u
        int s = dist[0][u] + dist[1][u] + dist[2][u];
        if(s < best){ best = s; meet = u; }
    }

    if(meet == -1){ cout << "no such city\n"; return; }

    // tiny route printer that walks parent[k] from meet back to src[k]
    auto printPath = [&](int k, const string& label){
        vector<int> rev; // meet -> ... -> src
        for(int cur = meet; cur != -1; cur = parent[k][cur]) rev.push_back(cur);
        cout << label;
        // print reversed order: src -> ... -> meet
        for(int i=(int)rev.size()-1; i>=0; --i){
            cout << indexToCity[rev[i]];
            if(i>0) cout << " to ";
        }
        int hops = (int)rev.size() - 1;
        cout << " (" << hops << " connections)\n";
        return hops;
    };

    cout << "You three should meet at " << indexToCity[meet] << "\n";
    int cA = printPath(0, "Route for first person: ");
    int cB = printPath(1, "Route for second person: ");
    int cC = printPath(2, "Route for third person: ");
    cout << "Total number of connection: " << (cA + cB + cC) << "\n";
}

void choseFunctionOne(vector<string>& indexToCity , vector<vector<int>>& adjacencyList, unordered_map<string, vector<string>>& map) {

    int from, to, maxConnections;

    printCities(map);   

    cout << "Choose the city you are travelling From: " << endl;
    cin >> from;

    cout << "Choose the city you are travelling To: " << endl;
    cin >> to;

    cout << "Choose the maximum amount of connections " << endl;
    cin >> maxConnections;

    functionOne(adjacencyList, from, to, maxConnections, indexToCity);
    
    return;
    
}

void choseFunctionTwo(vector<string>& indexToCity, vector<vector<int>>& adjacencyList, unordered_map<string, vector<string>>& map) {

    int from, to, connectOne, connectTwo;

    printCities(map);  
    
    cout << "Choose the city you are travelling From: " << endl;
    cin >> from;

    cout << "Choose the city you are travelling To: " << endl;
    cin >> to;

    cout << "Choose the first city you are connecting through: " << endl;
    cin >> connectOne;

    cout << "Choose the second city you are connecting through: " << endl;
    cin >> connectTwo;

    functionTwo(adjacencyList, from, to, connectOne, connectTwo, indexToCity);
    
    return;
}

void choseFunctionThree(vector<string>& indexToCity, vector<vector<int>>& adjacencyList, unordered_map<string, vector<string>>& map) {

    int startingCity;
    printCities(map);

    cout << "Choose the int value representing the country you are flying from: " << endl;
    cin >> startingCity;

    functionThree(adjacencyList, startingCity, indexToCity);

    return;

}

void choseFunctionFour(vector<string>& indexToCity, vector<vector<int>>& adjacencyList, unordered_map<string, vector<string>>& map) {

    int cityA, cityB, cityC;
    printCities(map);  

    cout << "Please choose City 1: " << endl;
    cin >> cityA;
    cout << "Please choose City 2: " << endl;
    cin >> cityB;
    cout << "Please choose City 3: " << endl;
    cin >> cityC;

    functionFour(adjacencyList, indexToCity, cityA, cityB, cityC);

    return;
}

bool chooseFunction() {

    cout << endl << endl;
    cout << "Hello and Welcome to World Airlines!" << endl;
    cout << "What can we assist you with today?" << endl << endl;


    cout << "----------------------------------------------------------------------" << endl;
    cout << "Please choose one of the following four opperations" << endl << endl;

    cout << "1: Shortest path from City A to City B in X connections or less" << endl;
    cout << "2: " << endl;
    cout << "3: Shortest round trip from City A" << endl;
    cout << "4: Closest connecting City from Cities A, B, and C" << endl;
    cout << "-1: exit" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    int input;
    cin >> input;

    vector<string> indexToCity;
    unordered_map<string, vector<string>> map = readFile();
    int i = 0;
    //Used to show available countries to choose for function 1, also now fills indexToCity
    for (pair<string, vector<string>> pair : map) {
        indexToCity.push_back(pair.first);
    }
    vector<vector<int>> adjacencyList = toAdjacencyList(map, indexToCity);

    switch(input) {
        case 1:
            cout << "You have chosen Function 1!"<< endl << "Shortest path from City A to City B in X connections or less" << endl << endl;
            choseFunctionOne(indexToCity, adjacencyList, map);
            break;
        case 2:
            cout << "You have chosen Function 2!"<< endl << "";
            choseFunctionTwo(indexToCity, adjacencyList, map);
            break;
        case 3:
            cout << "You have chosen Function 3!"<< endl << "Shortest round trip from City A" << endl;
            choseFunctionThree(indexToCity, adjacencyList, map);
            break;
        case 4:
            cout << "You have chosen Function 4!"<< endl << "Closest connecting City from Cities A, B, and C" << endl << endl;
            choseFunctionFour(indexToCity, adjacencyList, map);
            break;
        default: 
            cout << "Exiting simulation" <<endl << endl << "Have a Great Day" << endl << endl;
            return false;

    }

    cout << "Would you like to continue? " << endl << "1: Continue" << endl << "2: Exit" << endl;
    int cont;
    cin >> cont;

    if(cont != 1) {cout << "Exiting Simulation" << endl; return false;}

    return true;
}

int main() {

    bool running = true;
    while(running) {
        running = chooseFunction();
    }

    return 0;
}
