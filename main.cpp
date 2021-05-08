#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "map.cc"
#include "airport.cc"
#include "network.cc"
#include "kdtree.cc"

#include <iostream>
#include <vector>
#include <string>

static Network network("tests/data/airports.txt", "tests/data/routes.txt");

int main(int argc, char *argv[]) {
	std::vector<std::string> inputs;
	for (int i = 0; i < argc; ++i) {
		inputs.push_back(argv[i]);
	}
	
	if (inputs[1] == "find_best_airport") {
		// ./flights find_best_airport <first_airport> <second_airport> <tolerance>
		if (argc < 4) {
			std::cout << "Not enough arguments" << std::endl;
		} else if (network.GetAirports().count(inputs[2]) == 0 || network.GetAirports().count(inputs[3]) == 0) {
			std::cout << "Invalid airports" << std::endl;
		} else {
			double tol = 0.25;
			if(argc==5) tol = std::stod(inputs[4]);
			else {
				std::cout << "No tolerance provided, using 0.25 as a default" << std::endl;
			}
			std::cout << "Finding best airport to meet..." << std::endl;
			std::cout << network.FindBestAirport(inputs[2], inputs[3], tol) << std::endl;
		}
	} else if (inputs[1] == "animate_bfs") {
		// ./flights animate_bfs <starting_airport> <gif_output_file> <last_frame_output_file>
		if (argc < 5) {
			std::cout << "Not enough arguments";
		} else if (network.GetAirports().count(inputs[2]) == 0) {
			std::cout << "Invalid airport" << std::endl;
		} else {
			std::cout << "Animating BFS from " << inputs[2] << "..." << std::endl;
			cs225::PNG png;
			png.readFromFile("mercator.png");
			Map map(png);
			map.Animate(network.GetGraph(), network.GetAirports(), inputs[2], inputs[3], inputs[4]);
			std::cout << "Animation successful!" << std::endl;
		}
	} else if (inputs[1] == "find_closest_airport") {
		// ./flights find_closest_airport <starting_latitude> <starting_longitude>
		if (argc < 4) {
			std::cout << "Not enough arguments" << std::endl;
		} else {
			std::cout << "Finding closest airport..." << std::endl;
			std::cout << network.FindClosestAirport(std::stod(inputs[2]), std::stod(inputs[3])) << std::endl;
		}
	}

	return 0;
}