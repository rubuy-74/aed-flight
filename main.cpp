#include <iostream>

#include "classes/Parser.h"
#include "classes/Utils.h"
#include "classes/Dataset.h"
#include "classes/Functions.h"
#include "classes/Coordinate.h"
#include "vector"
using namespace std;


int main() {
    Parser parser;
    list<vector<string>> rawFlights = parser.readFile("../dataset/flights.csv");
    list<vector<string>> rawAirlines = parser.readFile("../dataset/airlines.csv");
    list<vector<string>> rawAirports = parser.readFile("../dataset/airports.csv");

    Dataset dataset = Dataset(rawFlights, rawAirports, rawAirlines);

    Airport airport = Airport("CDG","Charles De Gaulle","Paris","France",Coordinate(49.012779,2.550000));

    Functions functions;
    cout << functions.getNumFlightsOutOfAnAirport(airport) << '\n';
    cout << functions.getNumAirlinesOfAnAirport(airport) << '\n';
    cout << functions.getNumDestinationsAirportsOfAnAirport(airport) << '\n';
    cout << functions.getNumDestinationsCountriesOfAnAirport(airport) << '\n';
    cout << functions.getNumDestinationsCitiesOfAnAirport(airport) << '\n';
    vector<string> topK = functions.topKAirports(7);
    for(string s : topK){
        cout << s << '\n';
    }

    return 0;
}
