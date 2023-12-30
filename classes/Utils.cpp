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

void Utils::showAirport(Airport *airport) {
    cout << airport->getCode() << '\n';
    cout << "   " << "Name: " << airport->getName() << '\n';
    cout << "   " << "City: " << airport->getCity() << '\n';
    cout << "   " << "Country: " <<airport->getCountry() << '\n';
    cout << "   " << "Coordinates: " <<airport->getCoordinates().getLatitude() << " " <<airport->getCoordinates().getLongitude() << '\n';
}

double Utils::computeDistance(Coordinate c1, Coordinate c2){
    double dist = sin(toRad(c1.getLatitude())) * sin(toRad(c2.getLatitude()))
                    + cos(toRad(c1.getLatitude())) * cos(toRad(c2.getLatitude()))
                    * cos(toRad(c1.getLongitude() - c2.getLongitude()));
    dist = acos(dist);
    dist *= 6371;
    return dist;
}