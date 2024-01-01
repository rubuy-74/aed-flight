#include <iostream>

#include "classes/Parser.h"
#include "classes/Dataset.h"
#include "classes/Functions.h"
#include "vector"
#include "classes/Menu.h"

using namespace std;


int main() {
    Parser parser;
    list<vector<string>> rawFlights = parser.readFile("../dataset/flights.csv");
    list<vector<string>> rawAirlines = parser.readFile("../dataset/airlines.csv");
    list<vector<string>> rawAirports = parser.readFile("../dataset/airports.csv");

    Dataset dataset = Dataset(rawFlights, rawAirports, rawAirlines);
    Functions functions = Functions(dataset);
    Menu menu = Menu(dataset,dataset.getNetwork(),functions);
    menu.showMainMenu();
    return 0;
}