#include "Airport.h"

Airport::Airport() {
    this->code = "";
    this->city = "";
    this->country = "";
    this->name = "";
    this->coordinates = Coordinate();
    this->flights = {};
}

Airport::Airport(string code){
    this->code = code;
    this->city = "";
    this->country = "";
    this->name = "";
    this->coordinates = Coordinate();
    this->flights = {};
}

Airport::Airport(string code, string name, string city, string country, Coordinate coordinates) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->coordinates = coordinates;
    this->flights = {};
}

string Airport::getName() const { return this->name; }

string Airport::getCity() const { return this->city; }

string Airport::getCode() const { return this->code; }

string Airport::getCountry() const { return this->country; }

Coordinate Airport::getCoordinates() const { return this->coordinates; }

vector<Flight *> Airport::getFlights() const {
    return this->flights;
}

void Airport::setFlights(const vector<Flight *> flights) {
    this->flights = flights;
}

void Airport::addFlight(Flight *flight) {
    this->flights.push_back(flight);
}

bool Airport::removeFlight(Flight *flight) {
    auto it = find(this->flights.begin(), this->flights.end(), flight);
    if(it != flights.end()){
        flights.erase(it);
        return true;
    }
    return false;
}

Airport::Airport(const Airport &airport) {
    this->code = airport.code;
    this->name = airport.name;
    this->country = airport.country;
    this->coordinates = airport.coordinates;
    this->city = airport.city;
    this->flights = airport.flights;
}
