#ifndef AED_FLIGHT_UTILS_H
#define AED_FLIGHT_UTILS_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "Airport.h"
#include "Airline.h"
/**
 * This structure is responsible for defining a full trip
 */
struct Trip{
    int stops;
    pair<Airport*, Airport*> source_destination;
    vector<Airport*> airports;
    vector<Flight*> flights;

    Trip(int stops, pair<Airport*, Airport*> src_dest, vector<Airport*> airports, vector<Flight*> flights)
        : stops(stops), source_destination(src_dest), airports(airports), flights(flights) {}
};
/**
 * This structure is responsible for defining user's restrictions for a trip
 */
struct Filters{
    vector<Airline> preferredAirlines;
    bool minimizeAirlines;
    vector<Airport> preferredAirports;

    Filters(vector<Airline> preferredAirlines, bool minimizeAirlines, vector<Airport> preferredAirports)
        : preferredAirlines(preferredAirlines), minimizeAirlines(minimizeAirlines), preferredAirports(preferredAirports) {}
};
/**
 * This class contains some useful functions to use along the project
 */
class Utils {
public:
    static void showRaw(std::list<std::vector<std::string>> raw);
    static void showAirport(Airport *airport);
    static void clearScreen();
    static void showFile(list<vector<string>> menu);
    static void drawPageAirports(vector<Airport *> airports);
    static void drawBox(vector<string> text);
    static double computeDistance(Coordinate c1, Coordinate c2);

    static void drawPageFlights(vector<Trip> trips,bool isPath);

};


#endif //AED_FLIGHT_UTILS_H
