#pragma once

#include "ProblemStructures.h"
#include <vector>

class Vehicle {
public:
	int id;
	int capacity;
	Depot originDepot;
	int maxRouteDuration;
	std::vector<Customer> route;

	Vehicle();
	Vehicle(int id, int maxRouteDuration, int capacity, Depot originDepot);
	
	bool vehicleAvailable(Vehicle vehicle, Customer customer);
	
	~Vehicle();
};

class SolutionInstance {
public:
	std::vector<Vehicle> vehicleList;

	SolutionInstance(std::vector<Depot> depots); //Generate structure, without solution
	void generateRandomSolution(std::vector<Customer> customers);
};



//SolutionInstance generateSolutionInstance();

void testRand();
