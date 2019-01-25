#pragma once
#include "ProblemStructures.cpp"

class Location {
public:
	int id, x, y;
};

class Depot : public Location {
public:
	int depotId;
	int maxRouteDuration;
	int maxVehicleLoad;
};

class Customer : public Location {
public:
	int customerNumber;
	int serviceDuration;
	int demand;
};