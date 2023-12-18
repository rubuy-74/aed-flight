#include "Airport.h"

Airport::Airport() {
    this->code = "";
    this->city = "";
    this->country = "";
    this->name = "";
    this->coordinates = Coordinate();
}

Airport::Airport(string code, string name, string city, string country, Coordinate coordinates) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->coordinates = coordinates;
}

string Airport::getName() const { return this->name; }

string Airport::getCity() const { return this->city; }

string Airport::getCode() const { return this->code; }

string Airport::getCountry() const { return this->country; }

Coordinate Airport::getCoordinates() const { return this->coordinates; }