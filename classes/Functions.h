//
// Created by afons on 19/12/2023.
//

#ifndef AED_FLIGHT_FUNCTIONS_H
#define AED_FLIGHT_FUNCTIONS_H

#include "Airport.h"
#include "Graph.h"
#include "vector"
#include <algorithm>
#include <unordered_set>

class Functions {
public:
    static unsigned int getNumFlightsOutOfAnAirport(Graph g, Airport airport);
    static int getNumAirlinesOfAnAirport(Graph g, Airport airport);
    static int getNumDestinationsAirportsOfAnAirport(Graph g, Airport airport);
    static int getNumDestinationsCitiesOfAnAirport(Graph g, Airport airport);
    static int getNumDestinationsCountriesOfAnAirport(Graph g, Airport airport);
    static bool findInVector(const vector<string>& v, const string& code);
    static vector<string> topKAirports(Graph g, int k);
    static unordered_map<string, int> getFlightsPerCity(Graph g);
    static unordered_map<string, int> getFlightsPerAirline(Graph g);
    static int getNumAirportsAtDistance(Graph g,Airport airport, int distance);
    static int getNumCititesAtDistance(Graph g, Airport airport, int distance);
    static int getNumCountriesAtDistance(Graph g,Airport airport,int distance);
    static unordered_set<Airport *> getArticulationPoints(Graph g);
};


#endif //AED_FLIGHT_FUNCTIONS_H
