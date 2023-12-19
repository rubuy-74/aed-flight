#include <iostream>

#include "classes/Parser.h"
#include "classes/Utils.h"
#include "classes/Dataset.h"
using namespace std;

int main() {
    Parser parser;
    list<vector<string>> rawFlights = parser.readFile("../dataset/flights.csv");
    list<vector<string>> rawAirlines = parser.readFile("../dataset/airlines.csv");
    list<vector<string>> rawAirports = parser.readFile("../dataset/airports.csv");

    Dataset dataset = Dataset(rawFlights, rawAirports, rawAirlines);

    for(pair<string, Airport *> p : dataset.getNetwork().getAirports()){
        cout << p.first << endl;
        cout << "--------" << endl;
        for(Flight* f : p.second->getFlights()){
            cout << p.second->getCode() << "->" << f->getDestination()->getCode() << "->" << f->getDistance() << endl;
        }
    }

    return 0;
}
