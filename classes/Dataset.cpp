#include "Dataset.h"
<<<<<<< HEAD
#include "Flight.h"
=======
>>>>>>> 61ba205 (first function)
#include <cmath>

Graph Dataset::getNetwork() const {
    return network;
}

double toRad(double degree){
    return degree/180 * M_PI;
}

double computeDistance(Coordinate c1, Coordinate c2){
    double dist = sin(toRad(c1.getLatitude())) * sin(toRad(c2.getLatitude()))
                    + cos(toRad(c1.getLatitude())) * cos(toRad(c2.getLatitude()))
                    * cos(toRad(c1.getLongitude() - c2.getLongitude()));
    dist = acos(dist);
    dist *= 6371;
    return dist;
}

Dataset::Dataset(list<vector<string>> rawFlights, list<vector<string>> rawAirports, list<vector<string>> rawAirlines){
    loadAirports(rawAirports);
    loadAirlines(rawAirlines);
    loadFlights(rawFlights);
}

void Dataset::loadAirports(list<vector<string>> rawAirports) {
    for(vector<string> airports : rawAirports){
        Airport airport = Airport(airports[0], airports[1], airports[2], airports[3], Coordinate(stof(airports[4]), stof(airports[5])));
        this->network.addAirport(airport);
    }
}

void Dataset::loadFlights(list<vector<string>> rawFlights) {
    for(vector<string> flight : rawFlights){
        Airport* srcAirport = network.findAirport(Airport(flight[0]));
        Airport* destAirport = network.findAirport(Airport(flight[1]));
        srcAirport->addFlight(new Flight(destAirport, this->airlines[flight[2]], computeDistance(srcAirport->getCoordinates(), destAirport->getCoordinates())));
    }
}

void Dataset::loadAirlines(list<vector<string>> rawAirlines) {
    for(vector<string> airline : rawAirlines){
        this->airlines[airline[0]] = Airline(airline[0], airline[1], airline[2], airline[3]);
    }
}



