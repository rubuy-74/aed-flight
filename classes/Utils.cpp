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
