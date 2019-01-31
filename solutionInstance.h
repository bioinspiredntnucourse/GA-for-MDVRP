#pragma once

#include "ProblemStructures.h"
#include <vector>

class Vehicle {
public:
	int id;
	int load;
	int capacity;
	Depot originDepot;
	int routeRange;
	int maxRouteRange;
	std::vector<Customer> route;

	Vehicle(int id, int maxRouteRange, int capacity, Depot originDepot);
	
	bool vehicleAvailable(Customer customer);
	
	~Vehicle();
};

class SolutionInstance {
public:
	std::vector<Vehicle> vehicleList;
	float fitness;

	SolutionInstance(std::vector<Depot> depots); //Generate structure, without solution
	void generateRandomSolution(std::vector<Customer> customers);
};



float distanceBetweenCoordinates(int x1, int y1, int x2, int y2);

void testRand();
