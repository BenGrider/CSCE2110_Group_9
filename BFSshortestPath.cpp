/***********************************************************
  Synopsis: read from city.name and flight.txt
            store the graph in a adjacency matrix
            search for the shortest path using BFS
            from source node to destination node
            going through two intermediary nodes
            irregardless of which intermediary node goes 1st
***********************************************************/
//for now this is still using WA.cpp as a placeholder file!

#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <queue>//added to make the BFS shortest path work
//I'm not implementing a user defined queue

using namespace std;

class Graph{
     public:
          Graph(int d);
          ~Graph(){};

          void print();
          void addEdge(int node1, int node2){ adj[node1][node2] = 1; };
     private: 
          int n;
          int adj[140][140]; // You may want to use adjacent list implementation for sparse graph instead
};

Graph::Graph(int d){
    for (int i=0; i < d; i++){
        for (int j=0; j < d; j++){
            adj[i][j] = 0;
        }
    }
    n = d;
};

void Graph::print(){
    for (int i=0; i < n; i++){
        cout << i << " -> ";
        for (int j=0; j < n; j++){
            if (adj[i][j]){
                cout << j << " ";
            }
        }
        cout << endl;
    }

};


struct strCmp 
{
    	bool operator()( const string s1, const string s2 ) const 
	    {
      		return s1 <s2;
    	}
};

//to map a city name with a unique integer
map<const string, int, strCmp> city;
vector<string> cityID;// implemented a dynamic memory of type string for printing names

// CODE FOR Q2!!!
//attempting on implementing BFS for shortest path
// BFS shortest path using adjacency matrix
vector<int> bfsShortestPath(const Graph& g, int start, int goal) //the function parameters are the adjacency matrices that uses the graph class and its members func's, with a source and dest node
{
    queue<vector<int>> q; //queue of dynamic memory vector STL using type int
    vector<bool>visited(140, false); //the first parameter is based on the constraints of the sample, 140 cities, each initialized to false as default values
    //this memory is for checking if the node's been visited
    q.push(start); //assigning source node to the dynamic memory
    visited[start] = true; //the initial source node is added as the 1st array data inside the boolean dynamic memory, assigned true
    //the source node id ranges from 0-140!
    while(!q.empty())// a while loop that visits all nodes that'll be adjacent to the source node until destination node is met
    {
        vector<int> path = q.front();// this will trace the path the BFS takes, think of it as a temp head node!
        
    }
}

int main(int argc, char *argv[]){
   int i,j, node1, node2,n;
   string line;


   cout << "Please enter the number of cities in your graph: " << endl;
   cout << "---------------------------------------------------" << endl;
   cin >> n;

   Graph graph(n);
 
   char lineChar[256];

   ifstream cityFile;//this opens city.name file!!!
   cityFile.open("city.name", ios::in);

   for (i = 0; i < n; i++){
      cityFile.getline(lineChar,256);
      line = lineChar;
      city[line] = i;
      cout << line << " is numbered as city " << city[line]<< endl;
   }

   cityFile.close();

  /* initialize adjacent matrix*/

   ifstream flightFile;//this opens flight.txt file!!!
   flightFile.open("flight.txt", ios::in);

   while (flightFile.getline(lineChar, 256)){
      /* if line constains From: */
      line = lineChar;

      if (line.find("From:", 0) == 0 ){
          line.erase(0,7);
          node1 = city[line];
      } else {
          line.erase(0,7);
          node2 = city[line];
          graph.addEdge(node1,node2);
      }
   }
   flightFile.close();

   /* print the graph */
   cout << endl << "The graph generated can be represented by the following adjacent matrix : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;
   graph.print();
}


