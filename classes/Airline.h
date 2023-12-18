#ifndef AED_FLIGHT_AIRLINE_H
#define AED_FLIGHT_AIRLINE_H

#include <string>

using namespace std;

class Airline {
    private:
        string code;
        string name;
        string callsign;
        string country;
    public:
        Airline();
        Airline(string code, string name, string callsign, string country);
        string getCode() const;
        string getName() const;
        string getCallsign() const;
        string getCountry() const;
};


#endif //AED_FLIGHT_AIRLINE_H