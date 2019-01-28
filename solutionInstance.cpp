#include "solutionInstance.h"
#include <stdlib.h>
#include <iostream>

Problem exProb;

SolutionInstance generateSolutionInstance(Problem problemLoc) {
	int numDepots;
	numDepots = problemLoc.depots.size();

	//Generate Vehicle function
	int i, j, depotVehicleCount;
	for (i = 0; i < numDepots; i++) {
		depotVehicleCount = problemLoc.depots[i].vehicleCount;
		for (j = 0; j < depotVehicleCount; j++) {
			//new vehicle
		}
	}
}

void testRand() {
	int v1;
	int v2;
	v1 = rand() % 100;
	v2 = rand() % 100;
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
}
