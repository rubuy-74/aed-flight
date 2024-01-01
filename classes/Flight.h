#ifndef AED_FLIGHT_FLIGHT_H
#define AED_FLIGHT_FLIGHT_H

#include <string>
#include "Airline.h"
#include "Airport.h"
#include "Graph.h"

using namespace std;
/**
 * This class creates Flight objects (graph edges) with the following attributes:
 * <ul>
 *  <li> Flight's destination
 *  <li> Flight's airline
 *  <li> Flight's distance
 */
class Flight {
    private:
        Airport* dest;
        Airline airline;
        double distance;
    public:
        Flight();
        Flight(Airport* dest, Airline airline, double distance);
        Airport* getDestination() const;
        Airline getAirline() const;
        double getDistance() const;
};


#endif //AED_FLIGHT_FLIGHT_H
