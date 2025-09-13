#include <iostream>
#include <string>
#include <fstream>

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

int main() {

    string appendFromCity = "What city is the passenger flying from?\n";
    string askToCity = "What city is the passenger flying to?\n";

    //planning on putting these into an array of answers for cases 2 and 4
    string fromCity;
    string toCity;
    int maxAllowedConnections;

    displayWelcome();

    int function1to4;
    cin >> function1to4;
    cout << "You have chosen function " << function1to4 << endl;

    return 0;
};