#ifndef AED_FLIGHT_AIRLINE_H
#define AED_FLIGHT_AIRLINE_H

#include <string>

using namespace std;
/**
 * This class creates Airline objects with the following attributes:
 * <ul>
 *  <li> Airline's code
 *  <li> Airline's name
 *  <li> Airline's call sign
 *  <li> Airline's country
 */
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
        bool operator==(const Airline& other) const {
            return this->code == other.code;
        }
};


#endif //AED_FLIGHT_AIRLINE_H
