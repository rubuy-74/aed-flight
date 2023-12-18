#ifndef AED_FLIGHT_FLIGHT_H
#define AED_FLIGHT_FLIGHT_H

#include <string>

using namespace std;

class Flight {
    private:
        string src;
        string dest;
        string airline;
        float distance;
    public:
        Flight();
        Flight(string src, string dest, string airline, float distance);
        string getSource() const;
        string getDestination() const;
        string getAirline() const;
        float getDistance() const;
};


#endif //AED_FLIGHT_FLIGHT_H
