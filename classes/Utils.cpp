//
// Created by rubem on 16-12-2023.
//

#include "Utils.h"

void Utils::showRaw(std::list<std::vector<std::string>> raw) {
    for (auto element: raw) {
        for (auto i: element) {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
}

void Utils::showAirport(Airport *airport) {
    cout << airport->getCode() << '\n';
    cout << "   " << "Name: " << airport->getName() << '\n';
    cout << "   " << "City: " << airport->getCity() << '\n';
    cout << "   " << "Country: " <<airport->getCountry() << '\n';
    cout << "   " << "Coordinates: " <<airport->getCoordinates().getLatitude() << " " <<airport->getCoordinates().getLongitude() << '\n';
}
