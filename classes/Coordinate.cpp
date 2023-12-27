#include "Coordinate.h"
#include <cmath>

Coordinate::Coordinate() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

Coordinate::Coordinate(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

double Coordinate::getLatitude() const { return this->latitude; }

double Coordinate::getLongitude() const { return this->longitude; }
