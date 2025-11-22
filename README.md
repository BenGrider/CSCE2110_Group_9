# CSCE2110_Group_9
World Airline Route Search for CSCE 2110 - Foundation of Data Structures

## Team Members
- **Ben Grider** -
-   Q1: Find shortest route between two cities
-   Q2: Find shortest route from initial city to final city, through a user specified # of intermediate cities
-   Q3: Shortest Closed walk
- **Alan Ortega** -
-   Report
- **Nhu Pham** -
-   Q4: Meeting point between three friends

---

## Project Description
This program simulates a **world airline route system** using a graph data structure. It loads flight information from `flight.txt` (which lists "From" and "To" cities) and answer four route-related questions using **Breadth-First Search** and other algorithms.

---

## How to Compile
Make sure `flight.txt` is in the same folder.
g++ world_airlines.cpp -o world_airlines

```bash
g++ world_airlines.cpp -o world_airlines
./world_airlines
