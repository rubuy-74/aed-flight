#include "Flight.h"

Flight::Flight() {
    this->dest = "";
    this->src = "";
    this->airline = "";
}

Flight::Flight(string src, string dest, string airline) {
    this->dest = dest;
    this->src = src;
    this->airline = airline;
}

string Flight::getAirline() const { return this->airline; }

string Flight::getDestination() const { return this->dest; }

string Flight::getSource() const { return this->src; }
