#ifndef AED_FLIGHT_DATASET_H
#define AED_FLIGHT_DATASET_H

#include "Graph.h"
#include <list>
#include <boost/functional/hash.hpp>


typedef unordered_map<pair<string,string>,vector<Airport*>,boost::hash<pair<string,string>>> hashCityAirport;
class Dataset {
    private:
        Graph network;

        unordered_map<string, Airline> airlines;
        hashCityAirport cityAirports;
    public:
        Dataset();
        Dataset(list<vector<string>> rawFlights, list<vector<string>> rawAirports, list<vector<string>> rawAirlines);
        void loadAirports(list<vector<string>> rawAirports);
        void loadFlights(list<vector<string>> rawFlights);
        void loadAirlines(list<vector<string>> rawAirlines);

        Graph getNetwork() const;
        hashCityAirport getCityAirports() const;
};


#endif //AED_FLIGHT_DATASET_H
