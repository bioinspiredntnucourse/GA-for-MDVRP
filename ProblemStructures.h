#pragma once
#include "ProblemStructures.cpp"
#include <vector>


class Location {
public:
	int id, x, y;
};

class Depot : public Location {
public:
	int depotId;
	int vehicleCount;
	int maxRouteRange;
	int maxVehicleCapacity;

	~Depot() { depotId = NULL; vehicleCount = NULL; maxRouteRange = NULL; maxVehicleCapacity = NULL; };
};

class Customer : public Location {
public:		
	int customerNumber;
	int serviceRange;
	int demand;
};


class Problem {
public:
	std::vector<Depot> depots;
	std::vector<Customer> customers;
};