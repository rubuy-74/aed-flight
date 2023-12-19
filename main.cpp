#include <iostream>

#include "classes/Parser.h"
#include "classes/Utils.h"
#include "classes/Dataset.h"
#include "classes/Functions.h"
#include "classes/Coordinate.h"
#include "vector"
using namespace std;


int main() {
    Parser parser;
    list<vector<string>> rawFlights = parser.readFile("../dataset/flights.csv");
    list<vector<string>> rawAirlines = parser.readFile("../dataset/airlines.csv");
    list<vector<string>> rawAirports = parser.readFile("../dataset/airports.csv");
    return 0;
}
