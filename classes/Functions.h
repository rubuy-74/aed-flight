//
// Created by afons on 19/12/2023.
//

#ifndef AED_FLIGHT_FUNCTIONS_H
#define AED_FLIGHT_FUNCTIONS_H

#include "Airport.h"
#include "Graph.h"
#include "vector"

class Functions {
public:
    static unsigned int getNumFlightsOutOfAnAirport(Graph g, Airport airport);
    static int getNumAirlinesOfAnAirport(Graph g, Airport airport);
    static int getNumDestinationsAirportsOfAnAirport(Graph g, Airport airport);
    static int getNumDestinationsCitiesOfAnAirport(Graph g, Airport airport);
    static int getNumDestinationsCountriesOfAnAirport(Graph g, Airport airport);
    static bool findInVector(const vector<string>& v, const string& code);
    static vector<string> topKAirports(Graph g, int k);
};


#endif //AED_FLIGHT_FUNCTIONS_H
