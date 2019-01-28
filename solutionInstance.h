#pragma once

#include "ProblemStructures.h"
#include <vector>

class Vehicle {
public:
	int id;
	int capacity;
	int originDepot;
	std::vector<int> route;
};

class SolutionInstance {
public:
	std::vector<Vehicle> vehicleList;
};



//SolutionInstance generateSolutionInstance();

void testRand();
