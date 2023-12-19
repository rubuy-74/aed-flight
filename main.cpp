#include <iostream>

#include "classes/Parser.h"
#include "classes/Utils.h"
#include "classes/Dataset.h"
using namespace std;


void dfsVisit(Airport *a, vector<Airport *> &res){
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
}


int main() {
    Parser parser;
    list<vector<string>> rawFlights = parser.readFile("../dataset/flights.csv");
    list<vector<string>> rawAirlines = parser.readFile("../dataset/airlines.csv");
    list<vector<string>> rawAirports = parser.readFile("../dataset/airports.csv");

    Dataset dataset = Dataset(rawFlights, rawAirports, rawAirlines);

    /* for(pair<string, Airport *> p : dataset.getNetwork().getAirports()){
        cout << p.first << endl;
        cout << "--------" << endl;
        for(Flight* f : p.second->getFlights()){
            cout << p.second->getCode() << "->" << f->getDestination()->getCode() << "->" << f->getDistance() << endl;
        }
    } */

    dfs(dataset.getNetwork());

    return 0;
}
