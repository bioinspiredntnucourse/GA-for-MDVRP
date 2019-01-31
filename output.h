#pragma once

#include "solutionInstance.h"
#include "ProblemStructures.h"
#include <sstream>
#include <string>
#include <iostream>

void makeSolutionFile(SolutionInstance &solutionInstance, Problem &problem) {
	std::ostringstream os;
	os << solutionInstance.fitness << "\n";
	
	int i, j, k, l;
	for (i = 0; i < problem.depots.size(); i++) {
		k = 0;
		for (j = 0; j < solutionInstance.vehicleList.size(); j++) {
			if (solutionInstance.vehicleList[j].originDepot.depotId == i) {
				os << i << k
					<< solutionInstance.vehicleList[j].routeRange
					<< solutionInstance.vehicleList[j].load
					<< solutionInstance.vehicleList[j].endDepot.id;
				for (l = 0; l < solutionInstance.vehicleList[j].route.size(); l++) {
					os << solutionInstance.vehicleList[j].route[l].customerNumber;
				}
				os << "\n";
				k++;
			}
		}
	}

	std::string s = os.str();
	std::cout << s;
}