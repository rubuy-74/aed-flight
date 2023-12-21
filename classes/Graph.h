#ifndef AED_FLIGHT_GRAPH_H
#define AED_FLIGHT_GRAPH_H


#include <unordered_map>
#include <unordered_set>
#include "Airport.h"
#include "Flight.h"
#include "Coordinate.h"
#include <queue>
#include <vector>
#include <unordered_map>

enum AIRPORT_OPTION {
    CODE,NAME
};

class Graph {
    private:
        unordered_map<string, Airport *> airports;
    public:
        Graph();
        Graph(unordered_map<string, Airport *> airports);
        Airport* findAirport(Airport airport);
        Airport* findAirport(string airportAtt, AIRPORT_OPTION airportOption);
        bool addAirport(const Airport airport);
        bool removeAirport(const Airport airport);
        unordered_map<string, Airport *> getAirports() const;
        vector<Airport *> dfs();
        vector<Airport *> dfs(Airport *airport);
        vector<Airport *> dfsAtDistance(Airport *airport,int distance);
        void dfsVisit(Airport *a, vector<Airport *> &res);
        vector<Airport *> bfs(Airport *airport);
        vector<Airport *> bfsAtDistance(Airport *airport,int distance);
        bool isDAG();
        int numConnectedComponents();
        unordered_set<Airport *> getArticulationPoints();
};

#endif //AED_FLIGHT_GRAPH_H
