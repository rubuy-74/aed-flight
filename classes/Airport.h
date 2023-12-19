#ifndef AED_FLIGHT_AIRPORT_H
#define AED_FLIGHT_AIRPORT_H

#include <string>
#include "Coordinate.h"

class Flight;

using namespace std;

class Airport {
    private:
        string code;
        string name;
        string city;
        string country;
        Coordinate coordinates;
        vector<Flight *> flights;
        bool visited;
    public:
        Airport();
        Airport(Airport const &airport);
        Airport(string code);
        Airport(string code, string name, string city, string country, Coordinate coordinates);

        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        Coordinate getCoordinates() const;

        vector<Flight *> getFlights() const;
        void setFlights(const vector<Flight *>);

        void addFlight(Flight *flight);
        bool removeFlight(Flight *flight);

        bool isVisited() { return visited; }
        void setVisited(bool b) { this->visited = b; }
};


#endif //AED_FLIGHT_AIRPORT_H
