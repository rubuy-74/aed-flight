#ifndef AED_FLIGHT_GRAPH_H
#define AED_FLIGHT_GRAPH_H


#include "Airport.h"
#include "Flight.h"

class Vertex {
    private:
        Airport airport;
        vector<Flight *> flights; // only outgoing (?)
    public:
        Vertex();
        Vertex(Airport airport);

        Airport getAirport() const;
        void setAirport(Airport airport);

        vector<Flight *> getFlights() const;
        void setFlights(const vector<Flight *>);

        void addFlight(Flight *flight);
        bool removeFlight(Flight *flight);
};


class Graph {
    private:
        unordered_map<string, Vertex *> airports;
    public:
        Graph();
        Graph(unordered_map<string, Vertex *> airports);
        Vertex* findAirport(Airport airport);
        bool addAirport(const Airport airport);
        bool removeAirport(const Airport airport);
        unordered_map<string, Vertex *> getAirports() const;
};


#endif //AED_FLIGHT_GRAPH_H
