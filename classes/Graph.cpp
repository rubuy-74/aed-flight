#include "Graph.h"

Vertex::Vertex(Airport airport) {
    this->airport = airport;
}

void Vertex::addFlight(Flight *flight) {
    this->flights.push_back(flight);
}

bool Vertex::removeFlight(Flight *flight) {
    auto it = find(this->flights.begin(), this->flights.end(), flight);
    if(it != flights.end()){
        flights.erase(it);
        return true;
    }
    return false;
}

Airport Vertex::getAirport() const {
    return this->airport;
}

void Vertex::setAirport(Airport airport) {
    this->airport = airport;
}

vector<Flight *> Vertex::getFlights() const {
    return this->flights;
}

void Vertex::setFlights(const vector<Flight *> flights) {
    this->flights = flights;
}

Airport Graph::findAirport(Airport airport) {
    auto it = find(this->airports.begin(), this->airports.end(), new Vertex(airport));
    if(it != airports.end()){
        return (*it)->getAirport();
    }
    return Airport();
}

bool Graph::addAirport(const Airport airport) {
    auto it = find(this->airports.begin(), this->airports.end(), new Vertex(airport));
    if(it != airports.end()){
        return false;
    }
    this->airports.push_back(new Vertex(airport));
    return true;
}

bool Graph::removeAirport(const Airport airport) {
    auto it = find(this->airports.begin(), this->airports.end(), new Vertex(airport));
    if(it != airports.end()){
        airports.erase(it);
        return true;
    }
    return false;
}
