//
// Created by rubem on 16-12-2023.
//

#include "Parser.h"
using namespace std;

std::vector<std::string> Parser::splitLine(std::string line,const std::string& delimiter) {
    size_t pos;
    string token;
    vector<string> result;
    while(line.find(delimiter) != string::npos) {
        pos = line.find(delimiter);
        token = line.substr(0,pos);
        result.push_back(token);
        line = line.substr(pos + delimiter.length());
    }
    result.push_back(line.substr(0));
    return result;
}
/**
 * Reads a given file.
 * Time Complexity: O(n)
 * @param path
 * @return a list of vector of the attributes of the objects to be created
 */
std::list<std::vector<std::string>> Parser::readFile(const std::string &path) {
    ifstream file(path);
    string line;
    list<vector<string>> result;
    while (getline(file,line)) {
        result.push_back(splitLine(line,","));
    }
    file.close();
    result.pop_front();
    return result;
}
