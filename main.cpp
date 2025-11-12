#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

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
/*

void choseFunctionOne(vector<string> indexToCity , vector<vector<int>> adjacencyList) {

int from, to, maxConnections;

    cout << "Choose the int value representing the country you are travelling From: " << endl;
    cin >> from;

    cout << "Choose the int value representing the country you are travelling To: " << endl;
    cin >> to;

    cout << "Choose the int value representing the amount of maximum connections " << endl;
    cin >> maxConnections;

    functionOne(adjacencyList, from, to, maxConnections, indexToCity);
    
    return;
    
}
//BFS Algorithim
//I am in city a, can I fly to city B, with less than x connections. Give the the smallest number of connections and tell me the route. If not tell me
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
*/
/*
void choseFunctionTwo(vector<string> indexToCity,vector<vector<int>> adjacencyList) {

    int from, to, connectOne, connectTwo;
    
    cout << "Choose the int value representing the country you are travelling From: " << endl;
    int from;
    cin >> from;

    cout << "Choose the int value representing the country you are travelling To: " << endl;
    int to;
    cin >> to;

    cout << "Choose the first int value representing the country you are connecting through: " << endl;
    cin >> connectOne;

    cout << "Choose the second int value representing the country you are connecting through: " << endl;
    cin >> connectTwo;

    functionTwo(adjacencyList, from, to, connectOne, connectTwo, indexToCity);
    
    return;
}

void functionTwo(vector<vector<int>> adjacencyList, int from, int to, int connectOne, int connectTwo, vector<string> indexToCity) {

}
*/

void dfs(int curr, vector<vector<int>>& adjacencyList, vector<bool>& visited, vector<int>& route) {
    visited[curr] = true;

    // for each neighbor in adjacencyList
    for(int neighbor : adjacencyList[curr]) {

        if(!visited[neighbor]) {

            //
            route.push_back(neighbor);

            dfs(neighbor, adjacencyList, visited, route);

            //add curr on return
            route.push_back(curr);
        }
    }
}

/*
vector<vector<int>> BFSSpanningTree(vector<vector<int>>& adjacencyList, int startingCity) {
    int size = adjacencyList.size();
    vector<vector<int>> spanningTree
    return spanningTree;
}
*/

void functionThree(vector<vector<int>> adjacencyList, int startingCity, vector<string> indexToCity) {
    //DFS from starting City
    //Go on walk
        //going from curr to neighbor -> add neighbor to route
        //on return, append curr again
    int size = adjacencyList.size();
    //create a boolean vector of size of list, then set all to false
    vector<bool> visited(size,false);
    //create route
    vector<int> route;

    route.push_back(startingCity);

    //start the walk
    dfs(startingCity, adjacencyList, visited, route);

    for(int i = 0 ; i < route.size() ; i++) {
        cout << indexToCity[route[i]];
        if(i+1 < route.size()) {cout << " | " ;}
    }
    cout << endl << endl;
}

int main() {
    int toCityInt;
    int fromCityInt;
    int maxConnections;
    vector<string> indexToCity;
    unordered_map<string, vector<string>> map = readFile();
    int i = 0;
    //Used to show available countries to choose for function 1, also now fills indexToCity
    for (pair<string, vector<string>> pair : map) {
        indexToCity.push_back(pair.first);
        cout << i++ << " - From: " << pair.first << endl;
    }
    vector<vector<int>> adjacencyList = toAdjacencyList(map, indexToCity);

    //choseFunctionOne(indexToCity, adjacencyList);
    //choseFunctionTwo(indexToCity, adjacencyList);
    functionThree(adjacencyList, 0, indexToCity);

    return 0;
}
