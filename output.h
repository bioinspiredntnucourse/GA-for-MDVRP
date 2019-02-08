#pragma once

#include "solutionInstance.h"
#include "ProblemStructures.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "Graphics.h"

inline void writeToFile(std::string content, std::string filename){
	std::cout << "Writing solution to file." << std::endl;
	ofstream myfile;
	myfile.open(filename);
	myfile << content;
	myfile.close();
}

inline void PlotGenerations(vector<SolutionInstance> generationBests) {
	if (generationBests.size() == 0) return;

	string inp = to_string(generationBests[0].fitness);
	for (int i = 1; i < generationBests.size(); i++) {
		inp += "," + to_string(generationBests[i].fitness);
	}
	string filename = "genTops.res";
	writeToFile(inp, filename);
	CallPy("generationPlot.py", filename);
}

inline void printSolutionRoute(SolutionInstance instance) {
	int i, j;
	std::cout << "Printing solution instance route";
	for (i = 0; i < instance.vehicleList.size(); i++) {
		std::cout << "Route " << i << ":     ";
		for (j = 0; j < instance.vehicleList[i].route.size(); j++) {
			std::cout << instance.vehicleList[i].route[j].customerNumber << "   ";
		}
		std::cout << std::endl;
	}
}

inline void makeSolutionFile(SolutionInstance &solutionInstance, Problem &problem, string filename) {
	std::ostringstream os;
	os << solutionInstance.fitness << "\n";
	
	int i, j, k, l;
	for (i = 0; i < problem.depots.size(); i++) {
		k = 0;
		for (j = 0; j < solutionInstance.vehicleList.size(); j++) {
			if (solutionInstance.vehicleList[j].originDepot.depotId == i) {
				os << i << " "
					<< k << " "
					<< solutionInstance.vehicleList[j].routeRange << "   "
					<< solutionInstance.vehicleList[j].load << "   "
					<< solutionInstance.vehicleList[j].endDepot.depotId << "    ";
				for (l = 0; l < solutionInstance.vehicleList[j].route.size(); l++) {
					os << solutionInstance.vehicleList[j].route[l].customerNumber << " ";
				}
				os << "\n";
				k++;
			}
		}
	}
	std::string s = os.str();
	std::cout << s;
	writeToFile(s, filename);
}

void DrawSolutionInstance(Problem &problem, SolutionInstance &solutionInstance);