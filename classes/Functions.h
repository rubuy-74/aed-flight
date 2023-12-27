#ifndef AED_FLIGHT_FUNCTIONS_H
#define AED_FLIGHT_FUNCTIONS_H

#include "Airport.h"
#include "Graph.h"
#include "vector"
#include "Dataset.h"
#include "Parser.h"
#include "Utils.h"
#include <unordered_set>
#include <unordered_map>

enum MENU_OPTION {
    FROMCITYTOCOORDINATES,FROMCOORDINATESTOCITY,FROMCOORDINATESTOAIRPORT,FROMAIRPORTTOCOORDINATES,FROMCITYTOAIRPORT,FROMAIRPORTTOCITY
};

class Functions {
    private:
        Dataset dataset;
    public:
        Functions();
        Functions(Dataset dataset);

        void setAllAirportsUnvisited();

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
        int getNumAirportsAtDistance(Airport *airport, int distance);
        int getNumCitiesAtDistance(Airport airport, int distance);
        int getNumCountriesAtDistance(Airport airport,int distance);

        // vii
        vector<Trip> maxTripStops(Airport *airport);
        vector<Trip>  maxTripsGraph();

        // ix
        unordered_set<Airport *> getArticulationPoints();

        bool findInVector(const vector<string>& v, const string& code);

        vector<Airport*> getAirportsFromCoordinates(Coordinate c);

        void getAllMinPaths(Airport* start, Airport* end, vector<Trip>& allMinPaths);

        vector<Trip> findMinPathByAirportCode(const string& s, const string& d);
        vector<Trip> findMinPathByAirportName(const string& s, const string& d);
        vector<Trip> findMinPathByCity(string s, string d);
        vector<Trip> findMinPathByCoordinates(Coordinate s,Coordinate d);

        vector<Trip> findMinPathBetweenCityAndAirport(const string& city, const string& airportCode, MENU_OPTION menuOption);
        vector<Trip> findMinPathBetweenCoordinatesAndAirport(Coordinate c, const string& airportCode, MENU_OPTION menuOption);
        vector<Trip> findMinPathBetweenCoordinatesAndCity(Coordinate c, const string& city, MENU_OPTION menuOption);
};


#endif //AED_FLIGHT_FUNCTIONS_H
