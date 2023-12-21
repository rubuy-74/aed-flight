#ifndef AED_FLIGHT_UTILS_H
#define AED_FLIGHT_UTILS_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "Airport.h"

class Utils {
public:
    static void showRaw(std::list<std::vector<std::string>> raw);
    static void showAirport(Airport *airport);
    static void clearScreen();
    static void showFile(list<vector<string>> menu);
    static void drawPageAirports(vector<Airport *> airports);
    static void drawBox(vector<string> text);
};


#endif //AED_FLIGHT_UTILS_H
