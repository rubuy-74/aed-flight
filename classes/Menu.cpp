#include "Menu.h"
#include "Parser.h"
#include <iostream>
#include <algorithm>


void Menu::showMainMenu() {
    string option = ""; // TO AVOID INVALID OPTION LINE
    list<vector<string>> mainMenu = parser.readFile("../docs/mainMenu");
    while(option != "0" && option != "1" && option != "2"){
        Utils::showFile(mainMenu);
        cout << "1 - See statistics about the Network" << '\n';
        cout << "2 - See best flight option" << '\n';
        if(option != "1" && option != "2" && option != ""){
            cout << "Invalid Option. Try Again" << '\n';
        }
        cout << "Choose an option (0 for Exit): ";
        cin >> option;
    }
    if(option == "0") return;
    switch (stoi(option)){
        case 1:
            showListingFunctionsMenu();
            break;
        case 2:
            showBestOption();
            break;
    }
}

bool isValidOption(string option,int numOptions){
    try {
        int option_int = stoi(option);
        if(option_int <= numOptions) return true;
    } catch (invalid_argument){
        return false;
    }
    return false;
}



void Menu::showListingFunctionsMenu() {
    string option = "";
    list<vector<string>> listingMenu = parser.readFile("../docs/listingMenu");
    int numOptions = 10;
    while(option != "0" && !isValidOption(option,numOptions)){
        Utils::showFile(listingMenu);
        cout << "1 - See Global number of airports and number of available flights" << '\n';
        cout << "2 - See number of flights out of an airport and from how many airlines" << '\n';
        cout << "3 - See number of flights per city/airline"<<'\n';
        cout << "4 - See number of different countries that a given airport/city flies to" <<'\n';
        cout << "5 - See number of destinations (airports, cities or countries) available for a\n given airport" << "\n";
        cout << "6 - See number of reachable destinations (airports, cities or countries) from a\n given airport in a"
                "maximum number of X stops" << "\n";
        cout << "7 - See trip(s) with the greatest number of stops from an airport" << "\n";
        cout << "8 - See the top-k airport with the greatest air traffic capacity" << "\n";
        cout << "9 - See the articulation points of the network" << "\n";
        cout << "10 - See trip(s) with the greatest number of stops between them\n";
        if(!isValidOption(option,numOptions) && option != ""){
            cout << "Invalid Option. Try Again" << '\n';
        }
        cout << "Choose Option (0 for Exit): ";
        cin >> option;
    }
    if(option == "0") {
        showMainMenu();
        return;
    }
    string second_option;
    showListingOption(option);
    showListingFunctionsMenu();
}

vector<string> getAirlines(){
    string input;
    cout << "Set of airlines separated by ' ': ";
    cin.ignore();
    getline(cin,input);
    return Parser::splitLine(input," ");
}

void Menu::showBestOption() {
    vector<Airport *> src = inputAirports("Source");
    vector<Airport *> dest = inputAirports("Destination");
    vector<Trip> trips = functions.findMinPath(src,dest);
    string option;
    string second_option;
    while(option != "1" && option != "2" && option != "0"){
        cout << "0 - Continue without filters\n1 - Select Airlines to travel\n2 - Minimize Airlines\n";
        cin >> option;
    }
    vector<string> res;
    switch (stoi(option)) {
        case 1:
            res = getAirlines();
            break;
        case 2:
            //minimizeAirlines();
            break;
    }
    Utils::drawPageFlights(trips, true);
    while(second_option != "0" && second_option != "1"){
        if(second_option != "0" && second_option != "") cout << "INVALID OPTION. TRY AGAIN\n";
        cout << "Exit(0) or Retry(1):";
        cin >> second_option;
    }
    if(second_option == "1") showBestOption();
    else showMainMenu();
}

vector<Airport *> Menu::inputAirports(string element){
    string option;
    while(option != "1" && option != "2" && option != "3"){
        cout << element << "\n";
        cout << "1 - Airport\n2 - City\n3 - Coordinates\n";
        cin >> option;
    }
    vector<Airport *> srcAirport;
    while(srcAirport.empty()){
        string src;
        cout << element <<": ";
        cin.ignore();
        getline(cin,src);
        switch (stoi(option)){
            case 1: {
                srcAirport = functions.convertAirportToAirports(src);
                break;
            }
            case 2: {
                srcAirport = functions.convertCityToAirports(src);
                break;
            }
            case 3: {
                srcAirport = functions.convertCoordsToAirports(src);
                break;
            }
        }
    }
    return srcAirport;
}

void Menu::showListingOption(string option) {
    string second_option = "";
    while(second_option != "0"){
        second_option = "";
        Utils::clearScreen();
        switch (stoi(option)) { // IT IS A VALID OPTION
            case 1:
                break;
            case 2:
                // See number of flights out of an aiport and from how many airlines
                showOption2();
                break;
            case 3:
                // "3 - See number of flights per city/airline"<<'\n';
                showOption3();
                break;
            case 4:
                //"4 - See number of different countries that a given airport/city flies to" <<'\n';
                showOption4();
                break;
            case 5:
                //"5 - See number of destinations (airports, cities or countries) available for a given airport"
                showOption5();
                break;
            case 6:
                //"6 - See number of reachable destinations (airports, cities or countries) from a given airport in a\n"
                //                "maximum number of X stops"
                showOption6();
                break;
            case 7:
                // "7 - See trip(s) with the greatest number of stops in between them"
                showOption7();
                break;
            case 8:
                //"8 - See the top-k airport with the greatest air traffic capacity"
                showOption8();
                break;
            case 9:
                // "9 - See the articulation points of the network"
                showOption9();
                break;
            case 10:
                showOption10();
                break;
        }
        while(second_option != "0" && second_option != "1"){
            if(second_option != "0" && second_option != "") cout << "INVALID OPTION. TRY AGAIN\n";
            cout << "Exit(0) or Retry(1):";
            cin >> second_option;
        }
    }
}

void Menu::showOption2() {
    cout << "Airport Code:" << '\n';
    string airportCode;
    vector<string> text;
    cin >> airportCode;
    auto ptrAirport = graph.findAirport(airportCode,CODE);
    if(ptrAirport == nullptr) {
        cout << "AIRPORT NOT FOUND" << '\n';
        return;
    }
    int numFlights = functions.getNumFlightsOutOfAnAirport(*ptrAirport);
    int numAirlines = functions.getNumAirlinesOfAnAirport(*ptrAirport);
    text.push_back("Airport: " + ptrAirport->getName());
    text.push_back("Number of flights: " + to_string(numFlights));
    text.push_back("Number of airlines: "  + to_string(numAirlines));
    Utils::drawBox(text);
}

void Menu::showOption3() {
    string option = "";
    while(option != "1" && option != "2"){
        cout << "City(1) or Airline(2):";
        cin >> option;
    }
    string text = "Number of flights: ";
    if(option == "1") {
        unordered_map<string,int> flightsPerCity = functions.getFlightsPerCity();
        string city;
        string s;
        cout << "City: ";
        cin.ignore();
        getline(cin,city);
        if(flightsPerCity[city] == 0) {text = "CITY NOT FOUND";}
        else {text += to_string(flightsPerCity[city]);}
    }
    if(option == "2") {
        unordered_map<string,int> flightsPerAirline = functions.getFlightsPerAirline();
        string airline;
        cout << "Airline Code:";
        cin.ignore();
        getline(cin,airline);
        if(flightsPerAirline[airline] == 0) {text = "AIRLINE NOT FOUND";}
        else {text += to_string(flightsPerAirline[airline]);}
    }
    Utils::drawBox({text});
}

void Menu::showOption4() {
    string option = "";
    while(option != "1" && option != "2"){
        cout << "City(1) or Airport(2):";
        cin >> option;
    }
    string text = "Number of destinations: ";
    if(option == "1") {
        string city;
        cout << "City: ";
        cin.ignore(); getline(cin,city);
        text += to_string(functions.getNumDestinationsFromCity(city));
    }
    if(option == "2") {
        string airport;
        cout << "Airport Code:";
        cin.ignore();
        getline(cin,airport);
        auto ptrAirport = graph.findAirport(airport,CODE);
        if(ptrAirport == nullptr) {
            text = "AIRPORT NOT FOUND";
            return;
        } else{
            text += to_string(functions.getReachableDestinationsFromAirport(*ptrAirport));
        }
    }
    Utils::drawBox({text});
}

void Menu::showOption5() {
    cout << "Airport Code:" << '\n';
    string airportCode;
    vector<string> text;
    cin >> airportCode;
    auto ptrAirport = graph.findAirport(airportCode,CODE);
    if(ptrAirport == nullptr) {
        cout << "AIRPORT NOT FOUND" << '\n';
        return;
    }
    int numAirports = functions.getNumDestinationsAirportsOfAnAirport(*ptrAirport);
    int numCities = functions.getNumDestinationsCitiesOfAnAirport(*ptrAirport);
    int numCountries = functions.getNumDestinationsCountriesOfAnAirport(*ptrAirport);
    text.push_back("Airport: " + ptrAirport->getName());
    text.push_back("Number of airports: " + to_string(numAirports));
    text.push_back("Number of cities: " + to_string(numCities));
    text.push_back("Number of countries: " + to_string(numCountries));
    Utils::drawBox(text);
}

void Menu::showOption6() {
    string airportCode;
    string distance;
    vector<string> text;
    cout << "Airport Code: ";
    cin >> airportCode;
    cout << "Number of Stops: ";
    cin >> distance;
    auto ptrAirport = graph.findAirport(airportCode,CODE);
    if(ptrAirport == nullptr || !std::all_of(distance.begin(),distance.end(), ::isdigit)) {
        cout << "AIRPORT NOT FOUND" << '\n';
        return;
    }
    int d = stoi(distance);
    int numAirports = functions.getNumAirportsAtDistance(ptrAirport,d);
    int numCities = functions.getNumCitiesAtDistance(*ptrAirport,d);
    int numCountries = functions.getNumCountriesAtDistance(*ptrAirport,d);
    text.push_back("Airport: " + ptrAirport->getName());
    text.push_back("Distance: " + distance);
    text.push_back("Number of airports: " + to_string(numAirports));
    text.push_back("Number of cities: " + to_string(numCities));
    text.push_back("Number of countries: " + to_string(numCountries));
    Utils::drawBox(text);
}

void Menu::showOption7() {
    cout << "Airport Code:" << '\n';
    string airportCode;
    vector<string> text;
    cin >> airportCode;
    auto ptrAirport = graph.findAirport(airportCode,CODE);
    if(ptrAirport == nullptr) {
        cout << "AIRPORT NOT FOUND" << '\n';
        return;
    }
    vector<Trip> maxTrips = functions.maxTripStops(ptrAirport);
    text.push_back("Airport: " + ptrAirport->getName());
    text.push_back("Max number of trips: " + to_string(maxTrips[0].stops));
    for(auto i : maxTrips){
        text.push_back(i.airports.first->getCode() + " -> " + i.airports.second->getCode());
    }
    Utils::drawBox(text);
}

void Menu::showOption8() {
    string input;
    vector<string> text;
    cout << "K: ";
    cin >> input;
    if(!std::all_of(input.begin(),input.end(), ::isdigit)){
        cout << "NOT VALID NUMBER" << '\n'; return;
    }
    text.push_back(functions.topKAirports(stoi(input))->getName());
    Utils::drawBox(text);
}

void Menu::showOption9() {
    vector<string> text;
    unordered_set<Airport *> articulationPoints = functions.getArticulationPoints();
    for(auto i : articulationPoints){
        text.push_back(i->getCode());
    }
    vector<Airport *> ap;
    for(auto a: articulationPoints)  ap.push_back(a);
    Utils::drawPageAirports(ap);
}

void Menu::showOption10() {
    Utils::drawPageFlights(functions.maxTripsGraph(), false);
}


