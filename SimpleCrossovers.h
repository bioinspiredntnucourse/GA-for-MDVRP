#pragma once
#include "solutionInstance.h"
#include <math.h>

vector<SolutionInstance> PartiallyMappedCrossover(const SolutionInstance &inst) {
	//get two random paths, might be the same
	Vehicle v1 = inst.vehicleList[rand() % inst.vehicleList.size()];
	Vehicle v2 = inst.vehicleList[rand() % inst.vehicleList.size()];

	//get two random points within path1, the second after the first
	// + 2 to include the depots
	int p1 = rand() % (v1.route.size() + 2);
	int p2 = (rand() % (v2.route.size() + 2 - p1)) + p1;

	Vehicle c1v1 = v1;
	//Vehicle c1v2 = v2;

	if (p1 == 0) {
		c1v1.originDepot = v1.originDepot;
	}

	SolutionInstance child1 = inst;
	SolutionInstance child2 = inst;
}