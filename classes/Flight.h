#ifndef AED_FLIGHT_FLIGHT_H
#define AED_FLIGHT_FLIGHT_H

#include <string>

using namespace std;

class Flight {
    private:
        string src;
        string dest;
        string airline;
    public:
        Flight();
        Flight(string src, string dest, string airline);
        string getSource() const;
        string getDestination() const;
        string getAirline() const;
};


#endif //AED_FLIGHT_FLIGHT_H
