#ifndef AED_FLIGHT_FUNCTIONS_H
#define AED_FLIGHT_FUNCTIONS_H

#include "Airport.h"
#include "Graph.h"
#include "vector"
#include "Dataset.h"
#include "Parser.h"
#include <unordered_set>
#include <unordered_map>

class Functions {
    private:
        Dataset dataset;
    public:
        Functions();
        Functions(Dataset dataset);

        // iv
        int getNumDestinationsFromCity(string city);
        int getReachableDestinationsFromAirport(Airport airport);

        // ii
        unsigned int getNumFlightsOutOfAnAirport(Airport airport);
        int getNumAirlinesOfAnAirport(Airport airport);

        // v
        int getNumDestinationsAirportsOfAnAirport(Airport airport);
        int getNumDestinationsCitiesOfAnAirport(Airport airport);
        int getNumDestinationsCountriesOfAnAirport(Airport airport);

        // viii
        vector<string> topKAirports(int k);

        // iii
        unordered_map<string, int> getFlightsPerCity();
        unordered_map<string, int> getFlightsPerAirline();

        // vi
        int getNumAirportsAtDistance(Airport airport, int distance);
        int getNumCitiesAtDistance(Airport airport, int distance);
        int getNumCountriesAtDistance(Airport airport,int distance);

        // vii
        vector<Trip> maxTripStops(Airport *airport);
        vector<Trip>  maxTripsGraph();

        // ix
        unordered_set<Airport *> getArticulationPoints();

        bool findInVector(const vector<string>& v, const string& code);
};


#endif //AED_FLIGHT_FUNCTIONS_H
