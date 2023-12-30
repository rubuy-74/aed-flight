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

vector<Airline> Menu::getAirlines(){
    string input;
    cout << "0 - Cancel" << '\n';
    cout << "Set of airlines separated by ' ': ";
    cin.ignore();
    getline(cin,input);
    vector<string> rawAirlines = Parser::splitLine(input," ");
    vector<Airline> res;
    for(auto s : rawAirlines){
        res.push_back(dataset.getAirlines()[s]);
    }
    return res;
}

vector<Airport> Menu::getAirport(){
    string input;
    cout << "Set of airportCodes separated by ' ': ";
    cin.ignore();
    getline(cin,input);
    vector<string> rawAirports = Parser::splitLine(input," ");
    vector<Airport> res;
    for(auto s : rawAirports){
        if(graph.findAirport(s,CODE) != nullptr)
            res.push_back(*graph.findAirport(s,CODE));
    }
    return res;
}

void Menu::showBestOption() {
    Utils::clearScreen();
    vector<Airport *> src = inputAirports("Source");
    if(src.empty()) {showMainMenu(); return;}
    Utils::clearScreen();
    cout << "Source:";
    for(auto a : src) cout << a->getCode() << ' ';
    cout << '\n';
    vector<Airport *> dest = inputAirports("Destination");
    cout << "Destination:";
    for(auto a : dest) cout << a->getCode() << ' ';
    cout << '\n';
    if(dest.empty()) {showMainMenu(); return;};
    string option;
    string second_option;
    Utils::clearScreen();
    vector<Trip> trips;
    vector<Airline> prefAirlines;
    bool minimizeFlights = false;
    vector<Airport> prefAirports;
    while(option != "0"){
        cout<<"--- Filters ---\n";
        cout << "1 - Select Airlines to travel\n2 - Minimize Airlines\n3 - Select Airports to travel\n0 - Continue\nOption:";
        cin >> option;

        if(std::all_of(option.begin(),option.end(), ::isdigit)){
            switch (stoi(option)) {
                case 1:
                    prefAirlines = getAirlines();
                    break;
                case 2:
                    minimizeFlights = true;
                    break;
                case 3:
                    prefAirports = getAirport();
                    break;
            }
        }
    }
    trips = functions.findMinPath(src,dest,Filters(prefAirlines,minimizeFlights,prefAirports));
    Utils::clearScreen();
    cout << "--- Current filters ---\n";
    cout << "Preferred Airlines: "; for(auto a : prefAirlines) cout << a.getCode() << " ";
    cout <<'\n';
    cout << "Minimize Airlines: "; cout << (minimizeFlights ? "true" : "false") << '\n';
    cout << "Preferred Airports: "; for(auto a: prefAirports) cout << a.getCode() << " ";
    cout <<'\n';
    if(trips.empty()){
        cout << "--- NO FLIGHTS AVAILABLE ---" << '\n';
    }
    else{
        cout << "--- AVAILABLE FLIGHTS ---" << '\n';
        for(int i = 0; i < trips.size(); i++) {
            Trip current = trips[i];
            cout << string(3,' ') + current.airports[0]->getCode();
            for(auto t : current.flights){
                cout <<" -> " << t->getDestination()->getCode() << "(" << t->getAirline().getCode() << ")";
            }
            cout << '\n';
        }
    }
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
    while(option != "1" && option != "2" && option != "3" && option != "0"){
        cout <<"--- "<< element<<" ---" << "\n";
        cout << "1 - Airport\n2 - City\n3 - Coordinates\n0 - Cancel\nOption:";
        cin >> option;
    }
    if(option == "0") return {};
    vector<Airport *> airport;
    int count = 0;
    while(airport.empty()){
        switch (stoi(option)){
            case 1: {
                airport.clear();
                string airportName;
                cout << "Airport:";
                if(count == 0) cin.ignore();
                getline(cin,airportName);
                airport = functions.convertAirportToAirports(airportName);
                break;
            }
            case 2: {
                airport.clear();
                string cityName;
                string countryName;
                cout << "City Name:";
                if(count == 0) cin.ignore();
                getline(cin,cityName);
                cout << "Country Name:";
                getline(cin,countryName);
                airport = functions.convertCityToAirports(cityName,countryName);
                break;
            }
            case 3: {
                airport.clear();
                string coords;
                cout << "Coordinates:";
                if(count == 0) cin.ignore();
                getline(cin,coords);
                airport = functions.convertCoordsToAirports(coords);
                break;
            }
        }
        count++;
    }
    return airport;
}

void Menu::showListingOption(string option) {
    string second_option = "";
    while(second_option != "0"){
        second_option = "";
        Utils::clearScreen();
        switch (stoi(option)) { // IT IS A VALID OPTION
            case 1:
                showOption1();
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
        while(second_option != "0" && second_option != "1"){
            if(second_option != "0" && second_option != "") cout << "INVALID OPTION. TRY AGAIN\n";
            cout << "Exit(0) or Retry(1):";
            cin >> second_option;
        }
    }
}
void Menu::showOption1() {
    vector<string> text;
    text.emplace_back("Number of airports: " + to_string(dataset.getNetwork().getAirports().size()));
    int numTotalFlights = 0;
    for(auto f : graph.getAirports()) numTotalFlights += f.second->getFlights().size();
    text.emplace_back("Number of flights: " + to_string(numTotalFlights));
    Utils::drawBox(text);
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
        hashFlightsCity flightsPerCity = functions.getFlightsPerCity();
        string city;
        cout << "City: ";
        cin.ignore();
        getline(cin,city);
        string country;
        cout << "Country: ";
        getline(cin,country);
        if(flightsPerCity[make_pair(city,country)] == 0) {text = "CITY NOT FOUND";}
        else {text += to_string(flightsPerCity[make_pair(city,country)]);}
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
        string country;
        cout << "Country: ";
        getline(cin,country);
        text += "City: "+city + ", Country: " + country;
        text += to_string(functions.getNumDestinationsFromCity(city,country));
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
    if(ptrAirport == nullptr) {
        cout << "AIRPORT NOT FOUND" << '\n';
        return;
    }
    if(!std::all_of(distance.begin(),distance.end(), ::isdigit)){
        cout << "NUMBER NOT VALID" <<'\n';
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
        text.push_back(i.source_destination.first->getCode() + " -> " + i.source_destination.second->getCode());
    }
    Utils::drawBox(text);
}

void Menu::showOption8() {
    string input;
    vector<Airport*> text;
    cout << "K: ";
    cin >> input;
    if(!std::all_of(input.begin(),input.end(), ::isdigit)){
        cout << "NOT VALID NUMBER" << '\n'; return;
    }
    for(Airport * a : functions.topKAirports(stoi(input))){
        text.push_back(a);
    }
    Utils::drawPageAirports(text);
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


