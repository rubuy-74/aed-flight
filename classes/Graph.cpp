#include "Graph.h"

Vertex::Vertex() {
    this->airport = Airport();
}

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

Graph::Graph() {
    this->airports = {};
}

Graph::Graph(unordered_map<string, Vertex *> airports) {
    this->airports = airports;
}

Vertex* Graph::findAirport(Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        return it->second;
    }
    return new Vertex();
}

bool Graph::addAirport(const Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        return false;
    }
    this->airports[airport.getCode()] = new Vertex(airport);
    return true;
}

bool Graph::removeAirport(const Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        airports.erase(it);
        return true;
    }
    return false;
}

unordered_map<string, Vertex *> Graph::getAirports() const {
    return this->airports;
}