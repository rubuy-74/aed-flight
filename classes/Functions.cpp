#include "Functions.h"
#include "Graph.h"
#include "vector"
#include "algorithm"

Functions::Functions() {
    this->dataset = Dataset();
}

Functions::Functions(Dataset dataset) {
    this->dataset = dataset;
}

int Functions::getNumAirportsAtDistance(Airport airport, int distance) {
    return dataset.getNetwork().bfsAtDistance(dataset.getNetwork().findAirport(airport),distance).size();
}

int Functions::getNumCitiesAtDistance(Airport airport, int distance) {
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
    for(auto flight : dataset.getNetwork().findAirport(airport)->getFlights()){
        if(!findInVector(v, flight->getAirline().getCode())){
            v.push_back(flight->getAirline().getCode());
        }
    }
    return v.size();
}

int Functions::getNumDestinationsAirportsOfAnAirport(Airport airport) {
    return getNumAirportsAtDistance(airport, 1);
}

int Functions::getNumDestinationsCitiesOfAnAirport(Airport airport) {
    return getNumCitiesAtDistance(airport, 1);
}

int Functions::getNumDestinationsCountriesOfAnAirport(Airport airport) {
    return getNumCountriesAtDistance(airport, 1);
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

unordered_set<Airport *> Functions::getArticulationPoints() {
    return dataset.getNetwork().getArticulationPoints();
}

int Functions::getNumDestinationsFromCity(string city) {
    int res = 0;
    auto mapped = dataset.getCityAirports();
    for(auto a : mapped[city]){
        res += getNumAirportsAtDistance(a, 1);
    }
    return res;
}

int Functions::getReachableDestinationsFromAirport(Airport airport) {
    return dataset.getNetwork().dfs(dataset.getNetwork().findAirport(airport)).size();
}

vector<Trip> Functions::maxTripStops(Airport *airport) {
    return dataset.getNetwork().bfsMaxDepth(airport);
}

vector<Trip> Functions::maxTripsGraph() {
    Graph network = dataset.getNetwork();
    unordered_map<int,vector<Trip>> res;
    for(auto a: network.getAirports()){
        auto value = maxTripStops(a.second);
        if(!value.empty()){
            for(auto e: value)
                res[value[0].stops].push_back(e);
        }
    }
    int diameter = 0;
    for(auto kv: res){
        diameter = max(diameter,kv.first);
    }
    return res[diameter];
}
