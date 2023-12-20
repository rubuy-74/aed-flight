//
// Created by afons on 19/12/2023.
//

#include "Functions.h"
#include "Graph.h"
#include "algorithm"
#include "vector"

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
