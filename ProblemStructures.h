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
	int maxRouteDuration;
	int maxVehicleLoad;
};

class Customer : public Location {
public:		
	int customerNumber;
	int serviceDuration;
	int demand;
};


class Problem {
public:
	std::vector<Depot> depots;
	std::vector<Customer> Customers;
};