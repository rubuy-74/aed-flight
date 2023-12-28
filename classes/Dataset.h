#ifndef AED_FLIGHT_DATASET_H
#define AED_FLIGHT_DATASET_H

#include "Graph.h"
#include <list>

class Dataset {
    private:
        Graph network;

        unordered_map<string, Airline> airlines;
        unordered_map<string, vector<Airport*>> cityAirports;
    public:
        Dataset();
        Dataset(list<vector<string>> rawFlights, list<vector<string>> rawAirports, list<vector<string>> rawAirlines);
        void loadAirports(list<vector<string>> rawAirports);
        void loadFlights(list<vector<string>> rawFlights);
        void loadAirlines(list<vector<string>> rawAirlines);

        Graph getNetwork() const;
        unordered_map<string, vector<Airport*>> getCityAirports() const;

    vector<Airport *> getAirports(string city);
};


#endif //AED_FLIGHT_DATASET_H
