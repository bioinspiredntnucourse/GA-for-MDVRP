#pragma once
#include "ProblemStructures.cpp"
#include <vector>
#include <iostream>

using namespace std;

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
	int serviceDuration;
	int demand;
};


class Problem {
public:
	string filename;
	std::vector<Depot> depots;
	std::vector<Customer> customers;
};


inline void DepotToStream(Depot &depot, ostream &os) {
	os << "depot id: " << depot.depotId << endl
		<< "x: " << depot.x << " y: " << depot.y << endl
		<< "maxVehicleCapacity: " << depot.maxVehicleCapacity << endl
		<< "maxRouteRange: " << depot.maxRouteRange << endl
		<< "vehicleCount: " << depot.vehicleCount << endl
		<< endl;
}
inline void CustomerToStream(Customer &customer, ostream &os) {
	os << "customer number: " << customer.customerNumber << endl
		<< "x: " << customer.x << " y: " << customer.y << endl
		<< "demand: " << customer.demand << endl
		<< "serviceDuration: " << customer.serviceDuration << endl
		<< endl;
}
inline void ProblemToStream(Problem &p, ostream &os) {
	for (auto i = p.depots.begin(); i != p.depots.end(); ++i) {
		DepotToStream(*i, os);
		os << endl;
	}
	for (auto i = p.customers.begin(); i != p.customers.end(); ++i) {
		CustomerToStream(*i, os);
		os << endl;
	}
}