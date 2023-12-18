#ifndef AED_FLIGHT_AIRPORT_H
#define AED_FLIGHT_AIRPORT_H

#include <string>
#include "Coordinate.h"

using namespace std;

class Airport {
    private:
        string code;
        string name;
        string city;
        string country;
        Coordinate coordinates;
    public:
        Airport();
        Airport(string code);
        Airport(string code, string name, string city, string country, Coordinate coordinates);
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        Coordinate getCoordinates() const;
};


#endif //AED_FLIGHT_AIRPORT_H
