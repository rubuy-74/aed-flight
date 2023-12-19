//
// Created by rubem on 16-12-2023.
//

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
};


#endif //AED_FLIGHT_UTILS_H
