#include "core/network.h"

#include <utility>
#include <fstream>
#include <sstream>
#include <regex>

Network::Network(const std::string& airports_filename, const std::string& flights_filename) {
    parseAirports(airports_filename);
    parseFlights(flights_filename);
}

void Network::parseAirports(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> components;
        std::string component;
        std::stringstream current_line(line);
        while (getline(current_line, component, ',')) {
            components.push_back(component);
        }
        if (components.size() == 14) {
            components[4].erase(remove(components[4].begin(), components[4].end(), '\"'), components[4].end());
            Airport a(components[4], std::stod(components[6]), std::stod(components[7]));
            graph_[a] = std::unordered_map<Airport, double>();
        }
    }
}

void Network::parseFlights(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> components;
        std::string component;
        std::stringstream current_line(line);
        while (getline(current_line, component, ',')) {
            components.push_back(component);
        }
        if (components.size() >= 5) {
            components[2].erase(remove(components[2].begin(), components[2].end(), '\"'), components[2].end());
            components[4].erase(remove(components[4].begin(), components[4].end(), '\"'), components[4].end());
            Airport a(components[2], 0, 0);
            Airport b(components[4], 0, 0);
            //@TODO implement great circle distance formula
            graph_[a][b] = 0;

        }
    }

}
