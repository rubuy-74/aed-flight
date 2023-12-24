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

double Coordinate::distanceBetweenTwoCoordinates(Coordinate c1, Coordinate c2){
    return sqrt(pow((c1.getLatitude() - c2.getLatitude()),2) + pow((c1.getLongitude() - c2.getLongitude()),2));
}
