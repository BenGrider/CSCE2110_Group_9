//Ben Grider, Nhu Pham, Alan Ortega - 2110.501 - World Airlines Project

World Airlines

Ben Grider, Nhu Pham, Alan Ortega - 11/21/25

-----------------------------------------------------------------------------------------------

CSCE2110_project_team9.zip includes this readme, world_airlines.cpp, Team9ProjectReport.pdf, and flight.txt dependancy.

world_airlines.cpp is the implementation of the World Airlines Flight Route Planner written in C++.

This program reads a list of flights to cities from flight.txt, builds an adjacency list,
and provides a menu interface to answer several questions:
    - Shortest path from City A to City B within X connections
    - Shortest path from City A to City B through two specific cities
    - Shortest round trip starting and ending at a chosen city
    - Best meeting city for three travelers, with smallest the total number of connections

-----------------------------------------------------------------------------------------------

HOW TO RUN 

g++ world_airlines.cpp -o world_airlines
./world_airlines

-----------------------------------------------------------------------------------------------

Implemented functions

getCityFromString:
    Takes a line from the input file and returns the sanitized city name substring.

readFile:
    Reads flight.txt and builds an unordered_map<string, vector<string>> where each key
    is a "from" city and the value is a list of directly reachable "to" cities.

toAdjacencyList:
    Converts the unordered_map<string, vector<string>> of city names into a
    vector<vector<int>> adjacency list using an indexToCity vector.

printCities:
    Prints the list of available cities with their corresponding indices.

functionOne:
    Uses BFS to find the shortest route from city A to city B using at most X connections.
    Prints the route and the smallest number of connections.

bfsHelper:
    Helper BFS function used by functionTwo to compute a single shortest path between two cities and store the path in a route vector.

functionTwo:
    Uses bfsHelper to compute both A -> C -> D -> B and A -> D -> C -> B.
    Chooses and prints the best route with the smallest number of flights
    Reports if no such route exists.

functionThree:
    Uses BFS from a starting city to find the shortest round trip that returns to
    the same city.
    Prints the route if it exists.

functionFour:
    Runs BFS from three starting cities (A, B, and C) to finds a meeting city that
    minimizes the total number of connections for all three travelers.
    Prints each traveler’s route and the total connections.

choseFunctionOne:
    Handles user input/output for Function 1 (A to B in X connections)
    Sanatizes input
    Calls functionOne

choseFunctionTwo:
    Handles user input/output for Function 2 (A to B through C and D)
    Sanatizes input
    Calls functionTwo.

choseFunctionThree:
    Handles user input/output for Function 3 (shortest round trip), sanatizes
    input
    Calls functionThree.

choseFunctionFour:
    Handles user input/output for Function 4 (best meeting city for three travelers),
    sanatizes input
    Calls functionFour.

chooseFunction:
    Displays the main 
    loads flight.txt,
    builds indexToCity and the adjacency list
    calls the chosen operation
    and handles the exit and continue questions

main:
    Runs a loop that repeatedly calls chooseFunction until the user chooses to exit.
