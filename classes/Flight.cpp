#include "Flight.h"

Flight::Flight() {
    this->dest = new Airport();
    this->airline = Airline();
    this->distance = 0;
}

Flight::Flight(Airport* dest, Airline airline, double distance) {
    this->dest = dest;
    this->airline = airline;
    this->distance = distance;
}

Airline Flight::getAirline() const { return this->airline; }

Airport* Flight::getDestination() const { return this->dest; }

double Flight::getDistance() const { return this->distance; }