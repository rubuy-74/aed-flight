#include <stack>
#include "Graph.h"
#include <algorithm>


Graph::Graph() {
    this->airports = {};
}

Graph::Graph(unordered_map<string, Airport *> airports) {
    this->airports = airports;
}

Airport* Graph::findAirport(Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        return it->second;
    }
    return new Airport();
}

Airport *Graph::findAirport(string airportCode) {
    auto it = this->airports.find(airportCode);
    if(it != airports.end()) return it->second;
    return nullptr;
}

bool Graph::addAirport(const Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        return false;
    }
    this->airports[airport.getCode()] = new Airport(airport);
    return true;
}

bool Graph::removeAirport(const Airport airport) {
    auto it = this->airports.find(airport.getCode());
    if(it != airports.end()){
        airports.erase(it);
        return true;
    }
    return false;
}

unordered_map<string, Airport *> Graph::getAirports() const {
    return this->airports;
}

vector<Airport *> Graph::dfs(){
    vector<Airport *> res;
    for(pair<string, Airport*> p : getAirports()){
        p.second->setVisited(false);
    }
    for(pair<string, Airport*> p : getAirports()){
        if(!p.second->isVisited()) dfsVisit(p.second, res);
    }
    return res;
}

vector<Airport *> Graph::dfs(Airport *airport) {
    vector<Airport *> res;
    if(airport == nullptr) return res;
    for(auto a : getAirports()) a.second->setVisited(false);
    dfsVisit(airport,res);
    return res;
}


void Graph::dfsVisit(Airport *a, vector<Airport *> &res){
    a->setVisited(true);
    res.push_back(a);
    for(Flight *f : a->getFlights()){
        if(!f->getDestination()->isVisited()){
            dfsVisit(f->getDestination(), res);
        }
    }
}

vector<Airport *> Graph::bfs(Airport *airport) {
    vector<Airport *> res;
    if(airport == nullptr) return res;
    for(auto a: getAirports()) a.second->setVisited(false);
    queue<Airport *> queueAirports;
    queueAirports.push(airport);
    airport->setVisited(true);
    while(! queueAirports.empty()){
        Airport *current = queueAirports.front(); queueAirports.pop();
        res.push_back(current);
        for(auto e: current->getFlights()){
            Airport *w = e->getDestination();
            if(! w->isVisited()){
                queueAirports.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

bool dfsIsDAG(Airport *airport);
bool Graph::isDAG() {
    for(auto a: getAirports()){
        a.second->setVisited(false);
        a.second->setProcessing(false);
    }
    for(auto a: getAirports()){
        Airport *airport = a.second;
        if(! airport->isVisited()){
            if(! dfsIsDAG(airport))
                return false;
        }
    }
    return true;
}

void dfsAtDistanceVisit(Airport *airport, int distance, vector<Airport *> &res);
vector<Airport *> Graph::dfsAtDistance(Airport *airport, int distance) {
    vector<Airport *> res;
    if(airport == nullptr) return res;
    if(distance == 0) return {airport};
    for(auto a : getAirports()) a.second->setVisited(false);
    dfsAtDistanceVisit(airport,distance,res);
    return res;
}

void dfsAtDistanceVisit(Airport *airport, int distance, vector<Airport *> &res){
    if(distance == 0){
        res.push_back(airport);
        return;
    }
    airport->setVisited(true);
    for(auto flight : airport->getFlights()){
        Airport *w = flight->getDestination();
        if(!w->isVisited())
            dfsAtDistanceVisit(w,distance-1,res);
    }
}

vector<Airport *> Graph::bfsAtDistance(Airport *airport, int distance) {
    vector<Airport *> res;
    if(airport == nullptr) return res;
    for(auto a : getAirports()) a.second->setVisited(false);
    queue<Airport *> q;
    q.push(airport);
    int level = 0;
    while(!q.empty() && level<= distance){
        size_t qSize = q.size();
        for(size_t i = 0; i < qSize; i++){
            Airport *w = q.front(); q.pop();
            if(level == distance){
                res.push_back(w);
            }
            for(auto flight : w->getFlights()){
                if(!flight->getDestination()->isVisited()){
                    q.push(flight->getDestination());
                }
                flight->getDestination()->setVisited(true);
            }
        }
        level++;
    }
    return res;
}

bool dfsIsDAG(Airport *airport){
    airport->setVisited(true);
    airport->setProcessing(true);
    for(Flight *flight : airport->getFlights()){
        Airport *w = flight->getDestination();
        if(w->isProcessing()) return false;
        if(!w->isVisited())
            if(!dfsIsDAG(w))
                return false;
    }
    airport->setProcessing(false);
    return true;
}

int Graph::numConnectedComponents() {
    for(auto a : getAirports()) a.second->setVisited(false);
    vector<Airport *> res;
    int count = 0;
    for(auto a : getAirports()){
        Airport *airport = a.second;
        if(!airport->isVisited()){
            count++;
            dfsVisit(airport,res);
        }
    }
    return count;
}

void dfs_art(Airport *a,stack<Airport *> &s,unordered_set<Airport *> &res,int parent, int &i);
unordered_set<Airport *> Graph::getArticulationPoints() {
    unordered_set<Airport *> res;
    stack<Airport *> s;
    int i = 0;
    int parent = -1;
    for(auto a: getAirports()) a.second->setVisited(false);
    for(auto a: getAirports()){
        if(! a.second->isVisited()){
            dfs_art(a.second,s,res,parent,i);
        }
    }
    return res;
}

void dfs_art(Airport *a,stack<Airport *> &s,unordered_set<Airport *> &res,int parent, int &i){
    a->setVisited(true);
    a->setNum(i);
    a->setLow(i);
    s.push(a);
    i++;
    int children = 0;
    a->setProcessing(true);
    for(auto flight : a->getFlights()){
        Airport *w = flight->getDestination();
        if(!w->isVisited()){
            children++;
            dfs_art(w,s,res,w->getNum(),i);
            a->setLow(min(a->getLow(),w->getLow()));
            if(parent != -1 && w->getLow() >= a->getNum())
                res.insert(a);
        }
        else if(w->isProcessing()){
            a->setLow(min(a->getLow(),w->getNum()));
        }
    }
    a->setProcessing(false);
    if(parent == -1 && children > 1) res.insert(a);
    s.pop();
}
