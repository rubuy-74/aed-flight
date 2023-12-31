//
// Created by rubem on 16-12-2023.
//

#ifndef AED_FLIGHT_PARSER_H
#define AED_FLIGHT_PARSER_H

#include <string>
#include <list>
#include <vector>
#include <fstream>
/**
 * The parser class is responsible for reading the given CSV files and creating the corresponding objects.
 */
class Parser {
public:
    static std::list<std::vector<std::string>> readFile(const std::string &file);
    static std::vector<std::string> splitLine(std::string line,const std::string& delimiter);
};


#endif //AED_FLIGHT_PARSER_H
