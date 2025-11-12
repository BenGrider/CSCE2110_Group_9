# CSCE2110_Group_9
World Airline Route Search for CSCE 2110 - Foundation of Data Structures

## Team Members
- **Nhu Pham** - Q1: Find shortest route between two cities
- **Ben Grider**
- **Alan Ortega**

---

## Project Description
This program simulates a **world airline route system** using a graph data structure. It loads flight information from `flight.txt` (which lists "From" and "To" cities) and answer four route-related questions using **Breadth-First Search** and other algorithms.

---

## How to Compile
Make sure `flight.txt` and `city.name` are in the same solder.

```bash
g++ -std=c++17 -O2 -o routeSearch routeSearch.cpp
