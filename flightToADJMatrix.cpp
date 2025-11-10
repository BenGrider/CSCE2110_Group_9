#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

int main() {
  string line;
  ofstream flightDirectory (flight.txt);
  if(flightDirectory.is_open()) {
    while(getline(flightDirectory,line)) {
      cout << line << endl;
    }
    flightDirectory.close();
  }
  else { cout << "file is closed"}
  
  return 0;
}; 




