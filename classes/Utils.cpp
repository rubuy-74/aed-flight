#include <unordered_map>
#include "Utils.h"
#include "cmath"

void Utils::showRaw(std::list<std::vector<std::string>> raw) {
    for (auto element: raw) {
        for (auto i: element) {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
}

double toRad(double degree){
    return degree/180 * M_PI;
}
/**
 * Calculates the distance between two coordinates using Haversine Formula
 * @param c1
 * @param c2
 * @returns the distance between the coordinates
 */
double Utils::computeDistance(Coordinate c1, Coordinate c2){
    double dist = sin(toRad(c1.getLatitude())) * sin(toRad(c2.getLatitude()))
                  + cos(toRad(c1.getLatitude())) * cos(toRad(c2.getLatitude()))
                    * cos(toRad(c1.getLongitude() - c2.getLongitude()));
    dist = acos(dist);
    dist *= 6371;
    return dist;
}

void Utils::showAirport(Airport *airport) {
    cout << airport->getCode() << '\n';
    cout << "   " << "Name: " << airport->getName() << '\n';
    cout << "   " << "City: " << airport->getCity() << '\n';
    cout << "   " << "Country: " <<airport->getCountry() << '\n';
    cout << "   " << "Coordinates: " <<airport->getCoordinates().getLatitude() << " " <<airport->getCoordinates().getLongitude() << '\n';
}
/**
 * Clears the terminal screen after input
 */
void Utils::clearScreen(){
#if defined(__linux__)
    system("clear");
#elif __APPLE__
    system("clear");
#elif _WIN32
    system("cls");
#endif
}


void Utils::showFile(list<vector<string>> menu){
    clearScreen();
    vector<string> text;
    Utils utils;
    for(auto v : menu){
        string s;
        for(auto c: v){
            s += c;
        }
        text.push_back(s);
    }
    Utils::drawBox(text);
}

void Utils::drawBox(vector<string> text) {
    int maxLength = 80;
    for(auto s : text) maxLength = max(maxLength,(int) s.length() + 4);
    cout << string(maxLength, '-') << '\n';
    for(auto s : text){
        cout << "| " + s + string(maxLength -(4+s.length()),' ') +" |" << '\n';
    }
    cout << string(maxLength, '-') << '\n';
}

void drawLine(Airport *a,unordered_map<string,int> attSize){
    cout << "| " + a->getCode() + string(attSize["code"] - a->getCode().length(),' ') +
            " | " + a->getName() + string(attSize["name"] - a->getName().length(),' ') +
            " | " + a->getCountry() + string(attSize["country"] - a->getCountry().length(),' ') +
            " | " + a->getCity() + string(attSize["city"] - a->getCity().length(), ' ') + " |\n";
}

unordered_map<string,int> getAttSize(vector<Airport *> airports){
    vector<string> att = {"code","name","country","city"};
    unordered_map<string,int> attSize;
    for(auto a: airports){
        attSize["code"] = max(attSize["code"],(int)a->getCode().length());
        attSize["name"] = max(attSize["name"],(int)a->getName().length());
        attSize["country"] = max(attSize["country"],(int)a->getCountry().length());
        attSize["city"] = max(attSize["city"],(int)a->getCity().length());
    }
    return attSize;
}

void Utils::drawPageAirports(vector<Airport *> airports) {
    unordered_map<string,int> attSize = getAttSize(airports);
    int sus = attSize["code"] + attSize["name"] + attSize["country"] + attSize["city"] + 8 + 5;
    string decision;
    int pageSize = 10;
    int numPages = airports.size()%pageSize  == 0 ? airports.size()/pageSize : airports.size()/pageSize + 1;
    int page = 0;
    do {
        clearScreen();
        cout << "NUMBER OF ARTICULATIONS POINTS: " << airports.size() << '\n';
        int numAirports = (pageSize*(page+1)) > airports.size() ? (airports.size()%pageSize) : pageSize;
        cout << string(sus,'-') << '\n';
        for(int i = 0; i < numAirports; i++) drawLine(airports[i+(pageSize*page)],attSize);
        cout << string(sus,'-') << '\n';
        do {
            cout << "Page " + to_string(page+1) + " of " + to_string(numPages) + " Pages\n";
            cout << "| 2 - Go to next Page | 1 - Go to last Page | 0- Leave |" <<'\n';
            cin >> decision;
        } while(decision != "0" && decision != "1" && decision != "2");
        if(decision == "2") page = min(page + 1,numPages-1);
        if(decision == "1") page = max(page-1,0);

    } while (decision != "0");
}

void Utils::drawPageTopKAirports(vector<Airport *> airports) {
    unordered_map<string,int> attSize = getAttSize(airports);
    int sus = attSize["code"] + attSize["name"] + attSize["country"] + attSize["city"] + 8 + 5;
    string decision;
    int pageSize = 10;
    int numPages = airports.size()%pageSize  == 0 ? airports.size()/pageSize : airports.size()/pageSize + 1;
    int page = 0;
    do {
        clearScreen();
        cout << "TOP-" << airports.size() << " AIRPORTS: "<< '\n';
        int numAirports = (pageSize*(page+1)) > airports.size() ? (airports.size()%pageSize) : pageSize;
        cout << string(sus,'-') << '\n';
        for(int i = 0; i < numAirports; i++) drawLine(airports[i+(pageSize*page)],attSize);
        cout << string(sus,'-') << '\n';
        do {
            cout << "Page " + to_string(page+1) + " of " + to_string(numPages) + " Pages\n";
            cout << "| 2 - Go to next Page | 1 - Go to last Page | 0- Leave |" <<'\n';
            cin >> decision;
        } while(decision != "0" && decision != "1" && decision != "2");
        if(decision == "2") page = min(page + 1,numPages-1);
        if(decision == "1") page = max(page-1,0);

    } while (decision != "0");
}

void drawTrip(Trip trip,int offset){
    int oof = offset - 19;
    cout << "| From " << trip.source_destination.first->getCode() << " to "
        << trip.source_destination.second->getCode() << string(oof,' ') << " |" <<'\n';
}

void drawTripPath(Trip trip,int offset){
    int oof = offset - 3 - 4*trip.flights.size();
    cout << "| ";
    cout << trip.airports[0]->getCode();
    cout << string(oof,' ') << "|\n";
}

void Utils::drawPageFlights(vector<Trip> trips, bool isPath) {
    int sus = 70;
    string decision;
    int pageSize = 10;
    int numPages = trips.size()%pageSize  == 0 ? trips.size()/pageSize : trips.size()/pageSize + 1;
    int page = 0;
    do {
        clearScreen();
        int numAirports = (pageSize*(page+1)) > trips.size() ? (trips.size()%pageSize) : pageSize;
        if(!isPath) cout << "Max Number of Stops:" << trips[0].stops << '\n';
        cout << string(sus,'-') << '\n';
        for(int i = 0; i < numAirports; i++) {
            Trip current = trips[i + (pageSize * page)];
            if(!isPath) {
                int oof = sus - 19;
                cout << "| From " << current.source_destination.first->getCode() << " to "
                     << current.source_destination.second->getCode() << string(oof,' ') << " |" <<'\n';
            }
            else {
                        int oof = sus - 3 - 4*current.flights.size();
                        cout << "| ";
                        cout << current.airports[0]->getCode();
                        cout << string(oof,' ') << "|\n";
            }
        }
        cout << string(sus,'-') << '\n';
        do {
            cout << "Page " + to_string(page+1) + " of " + to_string(numPages) + " Pages\n";
            cout << "| 2 - Go to next Page | 1 - Go to last Page | 0- Leave |" <<'\n';
            cin >> decision;
        } while(decision != "0" && decision != "1" && decision != "2");
        if(decision == "2") page = min(page + 1,numPages-1);
        if(decision == "1") page = max(page-1,0);

    } while (decision != "0");
}
