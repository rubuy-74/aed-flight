#include "Coordinate.h"

Coordinate::Coordinate() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

Coordinate::Coordinate(float latitude, float longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

float Coordinate::getLatitude() const { return this->latitude; }

float Coordinate::getLongitude() const { return this->longitude; }
