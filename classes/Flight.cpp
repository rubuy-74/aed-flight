#include "Flight.h"

Flight::Flight() {
    this->dest = Airport();
    this->src = Airport();
    this->airline = Airline();
    this->distance = 0;
}

Flight::Flight(Airport src, Airport dest, Airline airline, double distance) {
    this->dest = dest;
    this->src = src;
    this->airline = airline;
    this->distance = distance;
}

Airline Flight::getAirline() const { return this->airline; }

Airport Flight::getDestination() const { return this->dest; }

Airport Flight::getSource() const { return this->src; }

double Flight::getDistance() const { return this->distance; }