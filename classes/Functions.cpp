//
// Created by afons on 19/12/2023.
//

#include "Functions.h"
#include "Graph.h"
#include "algorithm"
#include "vector"
#include <queue>
#include <limits>
#include <unordered_set>
#include "math.h"

unsigned int Functions::getNumFlightsOutOfAnAirport(Airport airport) {
    return dataset.getNetwork().findAirport(airport)->getFlights().size();
}

bool Functions::findInVector(const vector<string>& v, const string& x){
    for(const auto& s : v){
        if(s == x) return true;
    }
    return false;
}

int Functions::getNumAirlinesOfAnAirport(Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : dataset.getNetwork().findAirport(airport)->getFlights()){
        if(!findInVector(v, flight->getAirline().getCode())){
            v.push_back(flight->getAirline().getCode());
            count++;
        }
    }
    return count;
}

int Functions::getNumDestinationsAirportsOfAnAirport(Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : dataset.getNetwork().findAirport(airport)->getFlights()){
        if(!findInVector(v,flight->getDestination()->getCode())){
            v.push_back(flight->getDestination()->getCode());
            count++;
        }
    }
    return count;
}

int Functions::getNumDestinationsCitiesOfAnAirport(Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : dataset.getNetwork().findAirport(airport)->getFlights()){
        if(!findInVector(v,flight->getDestination()->getCity())){
            v.push_back(flight->getDestination()->getCity());
            count++;
        }
    }
    return count;
}

int Functions::getNumDestinationsCountriesOfAnAirport(Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : dataset.getNetwork().findAirport(airport)->getFlights()){
        if(!findInVector(v,flight->getDestination()->getCountry())){
            v.push_back(flight->getDestination()->getCountry());
            count++;
        }
    }
    return count;
}

vector<string> Functions::topKAirports(int k) {
    vector<string> res;
    vector<Airport*> tmp;
    for(auto airport : dataset.getNetwork().getAirports()){
        tmp.push_back(airport.second);
    }
    sort(tmp.begin(),tmp.end(),[](Airport* a1, Airport* a2){
        return a1->getFlights().size() > a2->getFlights().size();
    });
    for(int i=0; i<k; i++){
        res.push_back(tmp[i]->getName());
    }
    return res;
}


unordered_map<string, int> Functions::getFlightsPerCity() {
    unordered_map<string,int> flightsPerCity;
    for(auto airports: dataset.getNetwork().getAirports()){
        for(auto flight : airports.second->getFlights()){
            flightsPerCity[airports.second->getCity()]++;
            flightsPerCity[flight->getDestination()->getCity()]++;
        }
    }
    return flightsPerCity;
}

unordered_map<string, int> Functions::getFlightsPerAirline() {
    unordered_map<string,int> flightsPerAirline;
    for(auto airports: dataset.getNetwork().getAirports()){
        for(auto flight:airports.second->getFlights()){
            flightsPerAirline[flight->getAirline().getName()]++;
        }
    }
    return flightsPerAirline;
}


int Functions::getNumAirportsAtDistance(Airport airport, int distance) {
    return dataset.getNetwork().bfsAtDistance(dataset.getNetwork().findAirport(airport),distance).size();
}

int Functions::getNumCititesAtDistance(Airport airport, int distance) {
    auto destinations = dataset.getNetwork().bfsAtDistance(dataset.getNetwork().findAirport(airport),distance);
    vector<string> cities;
    for(auto a : destinations){
        if(find(cities.begin(),cities.end(),a->getCity()) != cities.end())
            cities.push_back(a->getCity());
    }
    return cities.size();
}

int Functions::getNumCountriesAtDistance(Airport airport, int distance) {
    auto destinations = dataset.getNetwork().bfsAtDistance(dataset.getNetwork().findAirport(airport),distance);
    vector<string> countries;
    for(auto a: destinations){
        if(find(countries.begin(),countries.end(),a->getCountry()) != countries.end())
            countries.push_back(a->getCountry());
    }
    return countries.size();
}

unordered_set<Airport *> Functions::getArticulationPoints() {
    return dataset.getNetwork().getArticulationPoints();
}

void Functions::reversePath(vector<Airport *> &path) {
    int start = 0;
    unsigned end = path.size() - 1;

    while (start < end) {
        swap(path[start], path[end]);
        start++;
        end--;
    }
}

vector<Airport *> Functions::findMinPathByCity(string s, string d){
    vector<Airport *> result;
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for (const auto& airport : dataset.getNetwork().getAirports()) {
        const string& start = airport.second->getCity();
        if (start == s) {
            for (const auto& otherAirport : dataset.getNetwork().getAirports()) {
                if (otherAirport.second->getCity() == d) {
                    vector<Airport *> path = findMinPathByAirportCode(airport.first, otherAirport.first);
                    allMinPaths.push_back(path);
                    if (path.size() < minSize && !path.empty()) {
                        minSize = path.size();
                    }
                }
            }
        }
    }

    for(auto v : allMinPaths){
        if(v.size() == minSize){
            result = v;
            break;
        }
    }

    return result;
}


vector<Airport *> Functions::findMinPathByAirportName(string s, string d){
    Airport *start = dataset.getNetwork().findAirport(s,NAME);
    Airport *destination = dataset.getNetwork().findAirport(d,NAME);

    priority_queue<pair<int, Airport *>, vector<pair<int, Airport *>>, greater<>> p;
    unordered_map<Airport *, int> distances;
    unordered_map<Airport *, Airport *> parent;

    for (const auto& a : dataset.getNetwork().getAirports()) {
        distances[a.second] = numeric_limits<int>::max();
        parent[a.second] = nullptr;
    }

    distances[start] = 0;
    p.push({0, start});

    while (!p.empty()) {
        int current_distance = p.top().first;
        Airport *current = p.top().second;
        p.pop();

        if (current_distance > distances[current]) {
            continue;
        }

        for (Flight *flight : current->getFlights()) {
            Airport *neighbor = flight->getDestination();
            int new_distance = distances[current] + flight->getDistance();

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                parent[neighbor] = current;
                p.push({new_distance, neighbor});
            }
        }
    }

    vector<Airport *> path;
    Airport *current = destination;

    while (current != nullptr) {
        path.push_back(current);
        current = parent[current];
    }

    reversePath(path);

    return path;
}

vector<Airport *> Functions::findMinPathByAirportCode(string s, string d){
    Airport *start = dataset.getNetwork().findAirport(s,CODE);
    Airport *destination = dataset.getNetwork().findAirport(d,CODE);

    priority_queue<pair<int, Airport *>, vector<pair<int, Airport *>>, greater<>> p;
    unordered_map<Airport *, int> distances;
    unordered_map<Airport *, Airport *> parent;

    for (const auto& a : dataset.getNetwork().getAirports()) {
        distances[a.second] = numeric_limits<int>::max();
        parent[a.second] = nullptr;
    }

    distances[start] = 0;
    p.push({0, start});

    while (!p.empty()) {
        int current_distance = p.top().first;
        Airport *current = p.top().second;
        p.pop();

        if (current_distance > distances[current]) {
            continue;
        }

        for (Flight *flight : current->getFlights()) {
            Airport *neighbor = flight->getDestination();
            int new_distance = distances[current] + flight->getDistance();

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                parent[neighbor] = current;
                p.push({new_distance, neighbor});
            }
        }
    }

    vector<Airport *> path;
    Airport *current = destination;

    while (current != nullptr) {
        path.push_back(current);
        current = parent[current];
    }

    reversePath(path);

    return path;
}

vector<Airport *> Functions::findMinPathByCoordinates(Coordinate s,Coordinate d){
    vector<Airport *> result;
    vector<Airport *> start;
    vector<Airport *> destination;
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();
    double d_min1 = numeric_limits<double>::max();
    double d_min2 = numeric_limits<double>::max();
    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance1 = sqrt(pow((airport.second->getCoordinates().getLatitude()-s.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - s.getLongitude()),2));
        double distance2 = sqrt((pow((airport.second->getCoordinates().getLatitude()-d.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - d.getLongitude()),2)));
        if(distance1 < d_min1){
            d_min1 = distance1;
        }
        if(distance2 < d_min2){
            d_min2 = distance2;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double dist1 = sqrt((pow((airport.second->getCoordinates().getLatitude()-s.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - s.getLongitude()),2)));
        double dist2 = sqrt((pow((airport.second->getCoordinates().getLatitude()-d.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - d.getLongitude()),2)));
        if(dist1 == d_min1){
            start.push_back(airport.second);
        }
        else if(dist2 == d_min2){
            destination.push_back(airport.second);
        }
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            vector<Airport *> path = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(path);
            if (path.size() < minSize && !path.empty()) {
                minSize = path.size();
            }
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            result = v;
        }
    }

    return result;
}

vector<vector<Airport *>> Functions::findMinPathBetweenAirportCity(string airportCode, string city){
    vector<vector<Airport *>> res;
    vector<Airport *> destination;
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        if(airport.second->getCity() == city){
            destination.push_back(airport.second);
        }
    }

    for(const auto & airport_destination : destination){
        vector<Airport *> path = findMinPathByAirportCode(airportCode,airport_destination->getCode());
        allMinPaths.push_back(path);
        if(path.size() < minSize && !path.empty()){
            minSize = path.size();
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            res.push_back(v);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathBetweenCityAirport(string city, string airportCode){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        if(airport.second->getCity() == city){
            start.push_back(airport.second);
        }
    }

    for(const auto & airport_source : start){
        vector<Airport *> path = findMinPathByAirportCode(airport_source->getCode(),airportCode);
        allMinPaths.push_back(path);
        if(path.size() < minSize && !path.empty()){
            minSize = path.size();
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            res.push_back(v);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathBetweenAirportCoordinates(string airportCode, Coordinate c){
    vector<vector<Airport *>> res;
    vector<Airport *> destination;
    double d_min = numeric_limits<double>::max();
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance < d_min){
            d_min = distance;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance == d_min){
            destination.push_back(airport.second);
        }
    }

    for(const auto & airport_destination : destination){
        vector<Airport *> path = findMinPathByAirportCode(airportCode,airport_destination->getCode());
        allMinPaths.push_back(path);
        if(path.size() < minSize && !path.empty()){
            minSize = path.size();
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            res.push_back(v);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathBetweenCoordinatesAirport(Coordinate c, string airportCode){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    double d_min = numeric_limits<double>::max();
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance < d_min){
            d_min = distance;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance == d_min){
            start.push_back(airport.second);
        }
    }

    for(const auto & airport_source : start){
        vector<Airport *> path = findMinPathByAirportCode(airport_source->getCode(),airportCode);
        allMinPaths.push_back(path);
        if(path.size() < minSize && !path.empty()){
            minSize = path.size();
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            res.push_back(v);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathBetweenCoordinatesCity(Coordinate c, string city){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    vector<Airport *> destination;
    double d_min = numeric_limits<double>::max();
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance < d_min){
            d_min = distance;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance == d_min){
            start.push_back(airport.second);
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        if(airport.second->getCity() == city){
            destination.push_back(airport.second);
        }
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            vector<Airport *> path = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(path);
            if (path.size() < minSize && !path.empty()) {
                minSize = path.size();
            }
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            res.push_back(v);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathBetweenCityCoordinnates(string city, Coordinate c){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    vector<Airport *> destination;
    double d_min = numeric_limits<double>::max();
    vector<vector<Airport *>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance < d_min){
            d_min = distance;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = sqrt((pow((airport.second->getCoordinates().getLatitude() - c.getLatitude()),2) + pow((airport.second->getCoordinates().getLongitude() - c.getLongitude()),2)));
        if(distance == d_min){
            destination.push_back(airport.second);
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        if(airport.second->getCity() == city){
            start.push_back(airport.second);
        }
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            vector<Airport *> path = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(path);
            if (path.size() < minSize && !path.empty()) {
                minSize = path.size();
            }
        }
    }

    for(const auto& v : allMinPaths){
        if(v.size() == minSize){
            res.push_back(v);
        }
    }

    return res;
}
