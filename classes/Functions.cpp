#include "Functions.h"
#include "Graph.h"
#include "vector"
#include <queue>
#include <limits>
#include <unordered_set>
#include "algorithm"
#include "Utils.h"
#include "set"

Functions::Functions() {
    this->dataset = Dataset();
}

Functions::Functions(Dataset dataset) {
    this->dataset = dataset;
}

int countUniqueAirlines(vector<Flight*> flights) {
    set<string> uniqueAirlines;
    for(auto flight : flights) {
        uniqueAirlines.insert(flight->getAirline().getCode());
    }
    return uniqueAirlines.size();
}

vector<Trip> getMinPathTrips(vector<Trip> allPaths, Filters filter) {
    vector<Trip> filteredStops;
    vector<Trip> filteredAirlines;

    sort(allPaths.begin(), allPaths.end(), [](Trip t1, Trip t2) {
        return t1.stops < t2.stops;
    });

    for (Trip t: allPaths) {
        if (t.stops == allPaths[0].stops) filteredStops.push_back(t);
    }
    if (filter.minimizeAirlines) {
        sort(filteredStops.begin(), filteredStops.end(), [](Trip t1, Trip t2) {
            return countUniqueAirlines(t1.flights) < countUniqueAirlines(t2.flights);
        });

        for (Trip t: filteredStops) {
            if (countUniqueAirlines(t.flights) == countUniqueAirlines(filteredStops[0].flights))
                filteredAirlines.push_back(t);
        }

        return filteredAirlines;
    }
    return filteredStops;
}

vector<Airport*> Functions::getAirportsFromCoordinates(Coordinate c){

    double minDistanceSource = numeric_limits<double>::max();
    vector<Airport*> res;

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distanceToSource = Utils::computeDistance(airport.second->getCoordinates(),c);

        if(distanceToSource < minDistanceSource) minDistanceSource = distanceToSource;
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distanceToSource = Utils::computeDistance(airport.second->getCoordinates(),c);

        if(abs(distanceToSource - minDistanceSource) < 0.000001) res.push_back(airport.second);
    }
    return res;
}

template<typename T>
vector<T> mergeVector(vector<T> t1, vector<T> t2){
    t1.insert(t1.end(), t2.begin(), t2.end());
    return t1;
}

void Functions::setAllAirportsUnvisited(){
    for(auto airport : dataset.getNetwork().getAirports()){
        airport.second->setVisited(false);
    }
}

int Functions::getNumAirportsAtDistance(Airport *airport, int distance) {
    return dataset.getNetwork().bfsAtDistance(airport,distance).size();
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
    return getNumAirportsAtDistance(dataset.getNetwork().findAirport(airport), 1);
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

bool checkAirlineFilter(Airline airline, vector<Airline> preferredAirlines){
    return find(preferredAirlines.begin(), preferredAirlines.end(), airline) != preferredAirlines.end();
}

bool checkAirportFilter(Airport *airport, vector<Airport> preferredAirports){
    return find(preferredAirports.begin(), preferredAirports.end(), *airport) != preferredAirports.end();
}

void Functions::getAllMinPaths(Airport* start, Airport* end, vector<Trip>& allMinPaths, Filters filter){

    setAllAirportsUnvisited();

    queue<Trip> q;

    Trip firstTrip = Trip(1, make_pair(start, nullptr), {start}, {});

    q.push(firstTrip);
    start->setVisited(true);

    while (!q.empty()) {
        Trip currentTrip = q.front();
        q.pop();
        Airport* current = currentTrip.airports.back();

        if(!allMinPaths.empty()) {
            if(currentTrip.stops + 1 > allMinPaths[0].stops) return;
        }

        for (auto neighbor : current->getFlights()) {
            if((filter.preferredAirlines.empty() || checkAirlineFilter(neighbor->getAirline(), filter.preferredAirlines)) && (filter.preferredAirports.empty() ||
                    checkAirportFilter(neighbor->getDestination(), filter.preferredAirports))){
                if(neighbor->getDestination() == end){
                    Trip minTrip = Trip(currentTrip.stops + 1, make_pair(start, neighbor->getDestination()),
                                                    mergeVector(currentTrip.airports, {neighbor->getDestination()}),
                                                    mergeVector(currentTrip.flights, {neighbor}));
                    allMinPaths.push_back(minTrip);
                }
                if (!neighbor->getDestination()->isVisited()) {
                    Trip toAdd = Trip(currentTrip.stops + 1, make_pair(start, neighbor->getDestination()),
                                                    mergeVector(currentTrip.airports, {neighbor->getDestination()}),
                                                mergeVector(currentTrip.flights, {neighbor}));
                    neighbor->getDestination()->setVisited(true);

                    q.push(toAdd);
                }
            }
        }
    }
}

vector<Airport*> Functions::serializeInput(const string &i){
    vector<Airport*> airports;
    if(!dataset.getCityAirports()[i].empty()){
        airports = dataset.getCityAirports()[i];
        return airports;
    }
    else if(dataset.getNetwork().findAirport(i,CODE) != nullptr) {
        airports = {dataset.getNetwork().findAirport(i,CODE)};
        return airports;
    }
    else if(dataset.getNetwork().findAirport(i,NAME) != nullptr){
        airports = {dataset.getNetwork().findAirport(i,NAME)};
        return airports;
    }
    // if it gets here it means that is a coordinate
    vector<string> coordinates = Parser::splitLine(i, " ");
    return getAirportsFromCoordinates(Coordinate(stod(coordinates[0]), stod(coordinates[1])));
}

vector<Trip> Functions::findMinPath(const string &s, const string &d, Filters filter) {
    vector<Trip> minPaths;
    vector<Airport *> start = serializeInput(s);
    vector<Airport *> dest = serializeInput(d);

    for (Airport *source: start) {
        for (Airport *destination: dest) {
            vector<Trip> paths;
            getAllMinPaths(source, destination, paths, filter);
            minPaths = mergeVector(minPaths, paths);
        }
    }
    return getMinPathTrips(minPaths, filter);
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
