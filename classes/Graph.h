#ifndef AED_FLIGHT_GRAPH_H
#define AED_FLIGHT_GRAPH_H


#include "Airport.h"
#include "Flight.h"
#include "unordered_map"

class Graph {
    private:
        unordered_map<string, Airport *> airports;
    public:
        Graph();
        Graph(unordered_map<string, Airport *> airports);
        Airport* findAirport(Airport airport);
        bool addAirport(const Airport airport);
        bool removeAirport(const Airport airport);
        unordered_map<string, Airport *> getAirports() const;
};


#endif //AED_FLIGHT_GRAPH_H
