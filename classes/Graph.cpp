#include "Graph.h"

Graph::Graph() {
    this->airports = {};
}

Graph::Graph(unordered_map<string, Airport *> airports) {
    this->airports = airports;
}

Airport* Graph::findAirport(Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        return it->second;
    }
    return new Airport();
}

bool Graph::addAirport(const Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        return false;
    }
    this->airports[airport.getCode()] = new Airport(airport);
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

unordered_map<string, Airport *> Graph::getAirports() const {
    return this->airports;
}