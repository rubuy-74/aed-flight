#ifndef AED_FLIGHT_UTILS_H
#define AED_FLIGHT_UTILS_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "Airport.h"

struct Trip{
    int stops;
    pair<Airport*, Airport*> airports;
    vector<Airport*> path;
};

class Utils {
public:
    static void showRaw(std::list<std::vector<std::string>> raw);
    static void showAirport(Airport *airport);
    static void clearScreen();
    static void showFile(list<vector<string>> menu);
    static void drawPageAirports(vector<Airport *> airports);
    static void drawBox(vector<string> text);
    static double computeDistance(Coordinate c1, Coordinate c2);
    static Trip createTrip(int stops, pair<Airport*, Airport*> airports, vector<Airport*> path);

    static void drawPageFlights(vector<Trip> trips,bool isPath);

};


#endif //AED_FLIGHT_UTILS_H
