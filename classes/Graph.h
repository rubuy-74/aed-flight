#ifndef AED_FLIGHT_GRAPH_H
#define AED_FLIGHT_GRAPH_H


#include "Airport.h"
#include "Flight.h"

class Vertex {
    private:
        Airport airport;
        vector<Flight *> flights; // only outgoing (?)

        void addFlight(Flight *flight);
        bool removeFlight(Flight *flight);
    public:
        Vertex(Airport airport);
        Airport getAirport() const;
        void setAirport(Airport airport);
        vector<Flight *> getFlights() const;
        void setFlights(const vector<Flight *>);
};


class Graph {
    private:
        vector<Vertex *> airports;
    public:
        Airport findAirport(Airport airport);
        bool addAirport(const Airport airport);
        bool removeAirport(const Airport airport);
};


#endif //AED_FLIGHT_GRAPH_H
