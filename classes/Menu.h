//
// Created by rubem on 19-12-2023.
//

#ifndef AED_FLIGHT_MENU_H
#define AED_FLIGHT_MENU_H


#include "Graph.h"
#include "Parser.h"
#include "Utils.h"
#include "Functions.h"

class Menu {
    Graph graph;
    Parser parser;
    Utils utils;
    Functions functions;
public:
    Menu(Graph graph) : graph(graph) {functions = Functions();};
    void showMainMenu();
    void showListingFunctionsMenu();
    void showBestOption();

    void showOption2();
    void showOption3();
    void showOption4();
    void showOption5();
    void showOption6();
    void showOption7();
    void showOption8();
    void showOption9();

    void showListingOption(string option);
};


#endif //AED_FLIGHT_MENU_H
