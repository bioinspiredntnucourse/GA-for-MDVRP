#pragma once
#include "solutionInstance.h"

vector<SolutionInstance> PartiallyMappedCrossover(const SolutionInstance &inst) {
	SolutionInstance child1 = inst;
	SolutionInstance child2 = inst;
	child1.vehicleList = inst.vehicleList;
	child2.vehicleList = inst.vehicleList;
}