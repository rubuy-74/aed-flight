#include <iostream>

#include "classes/Parser.h"
#include "classes/Utils.h"
#include "classes/Dataset.h"
#include "classes/Functions.h"
#include "classes/Coordinate.h"
#include "vector"
using namespace std;


/*void dfsVisit(Airport *a, vector<Airport *> &res){
    a->setVisited(true);
    res.push_back(a);
    for(Flight *f : a->getFlights()){
        if(!f->getDestination()->isVisited()){
            dfsVisit(f->getDestination(), res);
        }
    }
}

void dfs(Graph g){
    vector<Airport *> res;
    for(pair<string, Airport*> p : g.getAirports()){
        p.second->setVisited(false);
    }
    for(pair<string, Airport*> p : g.getAirports()){
        if(!p.second->isVisited()) dfsVisit(p.second, res);
    }
    int count = 0;
    for(Airport *a : res){
        cout << a->getCode() << endl << "----------" << endl;
        for(Flight *f: a->getFlights()){
            count++;
            cout << a->getCode() << " -> " << f->getDestination()->getCode() << " : " << f->getDistance() << "km" << endl;
        }
        cout << "----------" << endl;
    }
    cout << "Total flights (edges): " << count << endl;
    cout << "Total airports (nodes): " << res.size();
}*/


int main() {
    Parser parser;
    list<vector<string>> rawFlights = parser.readFile("../dataset/flights.csv");
    list<vector<string>> rawAirlines = parser.readFile("../dataset/airlines.csv");
    list<vector<string>> rawAirports = parser.readFile("../dataset/airports.csv");

    Dataset dataset = Dataset(rawFlights, rawAirports, rawAirlines);

    Airport airport = Airport("CDG","Charles De Gaulle","Paris","France",Coordinate(49.012779,2.550000));

    cout << Functions::getNumFlightsOutOfAnAirport(dataset.getNetwork(),airport) << '\n';
    cout << Functions::getNumAirlinesOfAnAirport(dataset.getNetwork(),airport) << '\n';
    cout << Functions::getNumDestinationsAirportsOfAnAirport(dataset.getNetwork(),airport) << '\n';
    cout << Functions::getNumDestinationsCountriesOfAnAirport(dataset.getNetwork(),airport) << '\n';
    cout << Functions::getNumDestinationsCitiesOfAnAirport(dataset.getNetwork(),airport) << '\n';
    vector<string> topK = Functions::topKAirports(dataset.getNetwork(),7);
    for(string s : topK){
        cout << s << '\n';
    }
    //dfs(dataset.getNetwork());

    return 0;
}
