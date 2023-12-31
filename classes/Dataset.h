#ifndef AED_FLIGHT_DATASET_H
#define AED_FLIGHT_DATASET_H

#include "Graph.h"
#include <list>
/**
 * This structure is responsible for defining an hash function for a more optimal lookup
 */
struct pairHashFunction{
    size_t operator()(const pair<string,string> p) const {
        string new_s = p.first + p.second;
        int hash_value = 0;
        for(char c : new_s) hash_value = 282943 * (toupper(c) - 'A');
        return hash_value;
    }
};
/**
 * This class is responsible for storing the program's data. It contains:
 * <ul>
 *  <li> A Graph
 *  <li> An hashmap that maps airline codes to it's correspondent object
 *  <li> An hashmap that maps a (city, country) pair to all the airports in it
 * <ul>
 */
typedef unordered_map<pair<string,string>,vector<Airport*>,pairHashFunction> hashCityAirport;
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
        unordered_map<string,Airline> getAirlines() const {return airlines;};
        hashCityAirport getCityAirports() const;
};


#endif //AED_FLIGHT_DATASET_H
