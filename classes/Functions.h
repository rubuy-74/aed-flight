//
// Created by afons on 19/12/2023.
//

#ifndef AED_FLIGHT_FUNCTIONS_H
#define AED_FLIGHT_FUNCTIONS_H

#include "Airport.h"
#include "Graph.h"
#include "vector"
#include "Dataset.h"
#include "Parser.h"
#include <unordered_set>
#include <unordered_map>

class Functions {
    Dataset dataset =Dataset(Parser::readFile("../dataset/flights.csv"),
    Parser::readFile("../dataset/airports.csv"),
    Parser::readFile("../dataset/airlines.csv"));;
public:
    unsigned int getNumFlightsOutOfAnAirport(Airport airport);
    int getNumAirlinesOfAnAirport(Airport airport);
    int getNumDestinationsAirportsOfAnAirport(Airport airport);
    int getNumDestinationsCitiesOfAnAirport(Airport airport);
    int getNumDestinationsCountriesOfAnAirport(Airport airport);
    bool findInVector(const vector<string>& v, const string& code);
    vector<string> topKAirports(int k);
    unordered_map<string, int> getFlightsPerCity();
    unordered_map<string, int> getFlightsPerAirline();
    int getNumAirportsAtDistance(Airport airport, int distance);
    int getNumCititesAtDistance(Airport airport, int distance);
    int getNumCountriesAtDistance(Airport airport,int distance);
    unordered_set<Airport *> getArticulationPoints();
};


#endif //AED_FLIGHT_FUNCTIONS_H
