#ifndef AED_FLIGHT_AIRPORT_H
#define AED_FLIGHT_AIRPORT_H

#include <string>
#include <vector>
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
        bool processing;
        int num;
        int low;
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

        bool isProcessing() {return processing;}
        void setProcessing(bool b) {this->processing = b;}

        int getNum() {return num;}
        void setNum(int num) {this->num = num;}

        int getLow() {return low;}
        void setLow(int low) {this->low = low;}

        bool operator==(const Airport& other) const {
            return this->code == other.code;
        }
};


#endif //AED_FLIGHT_AIRPORT_H
