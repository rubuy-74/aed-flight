//
// Created by rubem on 19-12-2023.
//

#include "Menu.h"
#include "Parser.h"
#include <iostream>

void clearScreen(){
    #if defined(__linux__)
        system("clear");
    #elif _WIN32
        system("cls");
    #endif
}


void showFile(list<vector<string>> menu){
    clearScreen();
    vector<string> res;
    Utils utils;
    for(auto v : menu){
        string s;
        for(auto c: v){
            s += c;
        }
        res.push_back(s);
    }
    utils.drawBox(res);
}

void Menu::showMainMenu() {
    string option = ""; // TO AVOID INVALID OPTION LINE
    list<vector<string>> mainMenu = parser.readFile("../docs/mainMenu");
    while(option != "0" && option != "1" && option != "2"){
        showFile(mainMenu);
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
    int numOptions = 9;
    while(option != "0" && !isValidOption(option,numOptions)){
        showFile(listingMenu);
        cout << "1 - See Global number of airports and number of available flights" << '\n';
        cout << "2 - See number of flights out of an airport and from how many airlines" << '\n';
        cout << "3 - See number of flights per city/airline"<<'\n';
        cout << "4 - See number of different countries that a given airport/city flies to" <<'\n';
        cout << "5 - See number of destinations (airports, cities or countries) available for a given airport" << "\n";
        cout << "6 - See number of reachable destinations (airports, cities or countries) from a given airport in a\n"
                "maximum number of X stops" << "\n";
        cout << "7 - See trip(s) with the greatest number of stops between them" << "\n";
        cout << "8 - See the top-k airport with the greatest air traffic capacity" << "\n";
        cout << "9 - See the articulation points of the network" << "\n";
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

void Menu::showBestOption() {
    cout << "best option selected" << '\n';
    showMainMenu();
}

void Menu::showListingOption(string option) {
    string second_option = "";
    while(second_option != "0"){
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
                break;
            case 5:
                //"5 - See number of destinations (airports, cities or countries) available for a given airport"
                break;
            case 6:
                //"6 - See number of reachable destinations (airports, cities or countries) from a given airport in a\n"
                //                "maximum number of X stops"
                break;
            case 7:
                // "7 - See trip(s) with the greatest number of stops in between them"
                break;
            case 8:
                //"8 - See the top-k airport with the greatest air traffic capacity"
                break;
            case 9:
                // "9 - See the articulation points of the network"
                break;
        }
        if(second_option != "0" && second_option != "") cout << "INVALID OPTION. TRY AGAIN\n";
        cout << "Exit(0): ";
        cin >> second_option;
    }
}

void Menu::showOption2() {
    clearScreen();
    cout << "Airport Code:" << '\n';
    string airportCode;
    vector<string> text;
    cin >> airportCode;
    if(graph.findAirport(airportCode) == nullptr) {
        cout << "AIRPORT NOT FOUND" << '\n';
        return;
    }
    auto airport = *graph.findAirport(airportCode);
    int numFlights = functions.getNumFlightsOutOfAnAirport(airport);
    int numAirlines = functions.getNumAirlinesOfAnAirport(airport);
    text.push_back("Airport: " + graph.findAirport(airportCode)->getName());
    text.push_back("Number of flights: " + to_string(numFlights));
    text.push_back("Number of airlines: "  + to_string(numAirlines));
    utils.drawBox(text);
}

void Menu::showOption3() {
    clearScreen();
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
        getline(cin >> s,city);
        cout << flightsPerCity[city] << '\n';
        if(flightsPerCity[city] == 0) {text = "CITY NOT FOUND";}
        else {text += to_string(flightsPerCity[city]);}
    }
    if(option == "2") {
        unordered_map<string,int> flightsPerAirline = functions.getFlightsPerAirline();
        string airline;
        cout << "Airline Code:";
        cin >> airline;
        cin.ignore();
        if(flightsPerAirline[airline] == 0) {text = "AIRLINE NOT FOUND";}
        else {text += to_string(flightsPerAirline[airline]);}
    }
    utils.drawBox(text);
}

void Menu::showOption4() {

}

void Menu::showOption5() {

}

void Menu::showOption6() {

}

void Menu::showOption7() {

}

void Menu::showOption8() {

}

void Menu::showOption9() {

}



