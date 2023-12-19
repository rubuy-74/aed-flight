//
// Created by afons on 19/12/2023.
//

#include "Functions.h"
#include "Graph.h"
#include "algorithm"
#include "vector"

unsigned int Functions::getNumFlightsOutOfAnAirport(Graph g, Airport airport) {
    return g.findAirport(airport)->getFlights().size();
}

bool Functions::findInVector(const vector<string>& v, const string& x){
    for(const auto& s : v){
        if(s == x) return true;
    }
    return false;
}

int Functions::getNumAirlinesOfAnAirport(Graph g, Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : g.findAirport(airport)->getFlights()){
        if(!findInVector(v, flight->getAirline().getCode())){
            v.push_back(flight->getAirline().getCode());
            count++;
        }
    }
    return count;
}

int Functions::getNumDestinationsAirportsOfAnAirport(Graph g, Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : g.findAirport(airport)->getFlights()){
        if(!findInVector(v,flight->getDestination()->getCode())){
            v.push_back(flight->getDestination()->getCode());
            count++;
        }
    }
    return count;
}

int Functions::getNumDestinationsCitiesOfAnAirport(Graph g, Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : g.findAirport(airport)->getFlights()){
        if(!findInVector(v,flight->getDestination()->getCity())){
            v.push_back(flight->getDestination()->getCity());
            count++;
        }
    }
    return count;
}

int Functions::getNumDestinationsCountriesOfAnAirport(Graph g, Airport airport) {
    vector<string> v;
    int count = 0;
    for(auto flight : g.findAirport(airport)->getFlights()){
        if(!findInVector(v,flight->getDestination()->getCountry())){
            v.push_back(flight->getDestination()->getCountry());
            count++;
        }
    }
    return count;
}

vector<string> Functions::topKAirports(Graph g, int k) {
    vector<string> res;
    vector<Airport*> tmp;
    for(auto airport : g.getAirports()){
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
