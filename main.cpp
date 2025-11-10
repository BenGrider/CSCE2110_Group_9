#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void displayWelcome() {
    string welcomeMessage = "\nWelcome to World Airlines! please choose one of the following options...\n\n";
    string askFlyAtoBWithinXConnections = "\tType 1: Find the shortest connections between City A to City B\n";
    string askFlyAtoDconnectingBandC = "\tType 2: Fly from City A to City B connecting through Cities C and D\n";
    string askFlyShortestRoundTrip = "\tType 3: Fly from city A through all available cities in a round trip\n";
    string askFlyConnectingThreeFlights = "\tType 4: Connect Three passengers to closest City\n";

    cout << welcomeMessage;
    cout << askFlyAtoBWithinXConnections;
    cout << askFlyAtoDconnectingBandC;
    cout << askFlyShortestRoundTrip;
    cout << askFlyConnectingThreeFlights << endl;
}

string getCountryFromString(string line) {
    string cleanedString = line.substr(7);
    return cleanedString;
};

void toMap() {

    string line;
    ifstream flightDirectory ("flight.txt");
    //unordered map acts as a key value pairs, with the key being the FROM country and the value being a vector of the destination countries
    unordered_map<string, vector<string>> map;
    bool isFrom;
    vector<string> toCountries, fromCountries;
    vector<vector<string>> allToCountries;
    string toCountry, fromCountry;


    //Gets all of the destinations and puts them in their respective vectors
    if(flightDirectory.is_open()) {
        while(getline(flightDirectory,line)) {

            string country = getCountryFromString(line);
            if(line.at(0) == 'F') { 
                fromCountries.push_back(country);
                if(!toCountries.empty()) { allToCountries.push_back(toCountries); }
                toCountries.clear();
            }
            else {
                toCountries.push_back(country);
            } 
            
    }
    allToCountries.push_back(toCountries);

    flightDirectory.close();
    }
    else { cout << "file is closed"; }
  
    //converts the vectors into a hashmap
    for(int i = 0 ; i < fromCountries.size() ; i++) {
        //map.insert(fromCountries[i], allToCountries[i]);
        map[fromCountries[i]] = allToCountries[i];
    }

    //Prints the hashmap
    for(pair<string, vector<string>> pair : map) {
        cout << "From: " << pair.first << endl << "\t";
        for(string s : pair.second) {
            cout << s << " | ";
        }
        cout << endl;
    }

};


int main() {

    string appendFromCity = "What city is the passenger flying from?\n";
    string askToCity = "What city is the passenger flying to?\n";

    //planning on putting these into an array of answers for cases 2 and 4
    string fromCity;
    string toCity;
    int maxAllowedConnections;

    toMap();
/*
    displayWelcome();

    int function1to4;
    cin >> function1to4;
    cout << "You have chosen function " << function1to4 << endl;
*/
    return 0;
};
