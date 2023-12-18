#include "Flight.h"

Flight::Flight() {
    this->dest = "";
    this->src = "";
    this->airline = "";
    this->distance = 0;
}

Flight::Flight(string src, string dest, string airline, float distance) {
    this->dest = dest;
    this->src = src;
    this->airline = airline;
    this->distance = distance;
}

string Flight::getAirline() const { return this->airline; }

string Flight::getDestination() const { return this->dest; }

string Flight::getSource() const { return this->src; }

float Flight::getDistance() const { return this->distance; }