#include "Functions.h"
#include "Graph.h"
#include "vector"
#include <queue>
#include <limits>
#include <unordered_set>
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

void Functions::bfs_all_paths(Airport* start, Airport* end, vector<vector<Airport*>>& allPaths){
    std::queue<std::vector<Airport*>> q;
    q.push({start});

    while (!q.empty()) {
        std::vector<Airport*> currentPath = q.front();
        q.pop();

        Airport* current = currentPath.back();

        if (current == end) {
            allPaths.push_back(currentPath);
        } else {
            for (auto neighbor : current->getFlights()) {
                if (!neighbor->getDestination()->isVisited()) {
                    std::vector<Airport*> newPath = currentPath;
                    newPath.push_back(neighbor->getDestination());
                    neighbor->getDestination()->setVisited(true);
                    q.push(newPath);
                }
            }
        }
    }
}

vector<vector<Airport *>> Functions::findMinPathByAirportName(const string& s, const string& d) {
    Airport *start = dataset.getNetwork().findAirport(s, NAME);
    Airport *destination = dataset.getNetwork().findAirport(d, NAME);

    if(start == nullptr || destination == nullptr){
        return {};
    }

    vector<vector<Airport*>> allPaths;
    bfs_all_paths(start, destination,allPaths);

    vector<vector<Airport *>> res;
    unsigned min = numeric_limits<int>::max();
    for(const auto& p : allPaths){
        if(p.size() < min){
            min = p.size();
        }
    }
    for(auto p : allPaths){
        if(p.size() == min){
            res.push_back(p);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathByAirportCode(const string& s, const string& d){
    Airport *start = dataset.getNetwork().findAirport(s, CODE);
    Airport *destination = dataset.getNetwork().findAirport(d, CODE);

    if(start == nullptr || destination == nullptr){
        return {};
    }

    vector<vector<Airport*>> allPaths;
    bfs_all_paths(start, destination,allPaths);

    vector<vector<Airport *>> res;
    unsigned min = numeric_limits<int>::max();
    for(const auto& p : allPaths){
        if(p.size() < min){
            min = p.size();
        }
    }
    for(auto p : allPaths){
        if(p.size() == min){
            res.push_back(p);
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::checkMinPaths(vector<vector<vector<Airport *>>> allMinPaths, unsigned minSize){
    vector<vector<Airport *>> res;
    for(const auto& v : allMinPaths){
        for(const auto& p : v){
            if(p.size() == minSize){
                res.push_back(p);
            }
        }
    }

    return res;
}

vector<vector<Airport *>> Functions::findMinPathByCity(string s, string d){
    vector<vector<Airport *>> result;
    vector<Airport *> start;
    vector<Airport *> destination;
    vector<vector<vector<Airport *>>> allMinPaths;
    unsigned minSize = numeric_limits<unsigned>::max();

    for(auto a : dataset.getNetwork().getAirports()){
        if(a.second->getCity() == s){
            start.push_back(a.second);
        }
        else if(a.second->getCity() == d){
            destination.push_back(a.second);
        }
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            airport_destination->setVisited(false);
            vector<vector<Airport *>> paths = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(paths);
            for(auto p : paths){
                if(p.size() < minSize){
                    minSize = p.size();
                }
            }
        }
    }

    return checkMinPaths(allMinPaths, minSize);
}

vector<vector<Airport *>> Functions::findMinPathByCoordinates(Coordinate s,Coordinate d){
    vector<vector<Airport *>> result;
    vector<Airport *> start;
    vector<Airport *> destination;
    vector<vector<vector<Airport *>>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();
    double d_min1 = numeric_limits<double>::max();
    double d_min2 = numeric_limits<double>::max();
    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance1 = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),s);
        double distance2 = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),d);
        if(distance1 < d_min1){
            d_min1 = distance1;
        }
        if(distance2 < d_min2){
            d_min2 = distance2;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance1 = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),s);
        double distance2 = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),d);
        if(abs(distance1 - d_min1) < 0.000001){
            start.push_back(airport.second);
        }
        else if(abs(distance2 - d_min2) < 0.000001){
            destination.push_back(airport.second);
        }
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            airport_destination->setVisited(false);
            vector<vector<Airport *>> paths = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(paths);
            for(auto p : paths){
                if(p.size() < minSize){
                    minSize = p.size();
                }
            }
        }
    }

    return checkMinPaths(allMinPaths, minSize);
}

vector<vector<Airport *>> Functions::findMinPathBetweenCityAndAirport(const string& city, const string& airportCode, MENU_OPTION menuOption){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    vector<Airport *> destination;
    //Airport *destination = dataset.getNetwork().findAirport(airportCode,CODE);
    vector<vector<vector<Airport *>>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        if(airport.second->getCity() == city){
            if(menuOption == FROMCITYTOAIRPORT){
                start.push_back(airport.second);
            }
            else if(menuOption == FROMAIRPORTTOCITY){
                destination.push_back(airport.second);
            }
        }
    }

    if(menuOption == FROMCITYTOAIRPORT){
        destination.push_back(dataset.getNetwork().findAirport(airportCode,CODE));
    }
    else if(menuOption == FROMAIRPORTTOCITY){
        start.push_back(dataset.getNetwork().findAirport(airportCode,CODE));
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            airport_destination->setVisited(false);
            vector<vector<Airport *>> paths = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(paths);
            for(const auto& p : paths){
                if(p.size() < minSize){
                    minSize = p.size();
                }
            }
        }
    }

    return checkMinPaths(allMinPaths, minSize);
}

vector<vector<Airport *>> Functions::findMinPathBetweenCoordinatesAndAirport(Coordinate c, const string& airportCode, MENU_OPTION menuOption){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    vector<Airport *> destination;
    double d_min = numeric_limits<double>::max();
    vector<vector<vector<Airport *>>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),c);
        if(distance < d_min){
            d_min = distance;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),c);
        if(abs(distance - d_min) < 0.000001){
            if(menuOption == FROMAIRPORTTOCOORDINATES){
                destination.push_back(airport.second);
            }
            else if(menuOption == FROMCOORDINATESTOAIRPORT){
                start.push_back(airport.second);
            }
        }
    }

    if(menuOption == FROMCOORDINATESTOAIRPORT){
        destination.push_back(dataset.getNetwork().findAirport(airportCode,CODE));
    }
    else if(menuOption == FROMAIRPORTTOCOORDINATES){
        start.push_back(dataset.getNetwork().findAirport(airportCode,CODE));
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            airport_destination->setVisited(false);
            vector<vector<Airport *>> paths = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(paths);
            for(const auto& p : paths){
                if(p.size() < minSize){
                    minSize = p.size();
                }
            }
        }
    }

    return checkMinPaths(allMinPaths, minSize);
}

vector<vector<Airport *>> Functions::findMinPathBetweenCoordinatesAndCity(Coordinate c, const string& city, MENU_OPTION menuOption){
    vector<vector<Airport *>> res;
    vector<Airport *> start;
    vector<Airport *> destination;
    double d_min = numeric_limits<double>::max();
    vector<vector<vector<Airport *>>> allMinPaths;
    unsigned minSize = numeric_limits<int>::max();

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),c);
        if(distance < d_min){
            d_min = distance;
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        double distance = Coordinate::distanceBetweenTwoCoordinates(airport.second->getCoordinates(),c);
        if(abs(distance - d_min) < 0.000001){
            if(menuOption == FROMCOORDINATESTOCITY){
                start.push_back(airport.second);
            }
            else if(menuOption == FROMCITYTOCOORDINATES){
                destination.push_back(airport.second);
            }
        }
    }

    for(const auto& airport : dataset.getNetwork().getAirports()){
        if(airport.second->getCity() == city){
            if(menuOption == FROMCOORDINATESTOCITY){
                destination.push_back(airport.second);
            }
            else if(menuOption == FROMCITYTOCOORDINATES){
                start.push_back(airport.second);
            }
        }
    }

    for(auto airport_source : start){
        for(auto airport_destination : destination){
            airport_destination->setVisited(false);
            vector<vector<Airport *>> paths = findMinPathByAirportCode(airport_source->getCode(), airport_destination->getCode());
            allMinPaths.push_back(paths);
            for(const auto& p : paths){
                if(p.size() < minSize){
                    minSize = p.size();
                }
            }
        }
    }

    return checkMinPaths(allMinPaths,minSize);
}

vector<Trip> Functions::maxTripStops(Airport *airport) {
    return dataset.getNetwork().bfsMaxDepth(airport);
}