#include "Airline.h"

Airline::Airline() {
    this->country = "";
    this->name = "";
    this->code = "";
    this->callsign = "";
}

Airline::Airline(string code, string name, string callsign, string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

string Airline::getCountry() const { return this->country; }

string Airline::getCode() const { return this->code; }

string Airline::getName() const { return this->name; }

string Airline::getCallsign() const { return this->callsign; }
