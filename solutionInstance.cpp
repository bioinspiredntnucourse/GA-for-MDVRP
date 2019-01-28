#include "solutionInstance.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

Vehicle::Vehicle(int id, int maxRouteRange, int capacity, Depot originDepot) {
	id = id;
	load = 0;
	capacity = capacity;
	originDepot = originDepot;
	routeRange = 0;
	maxRouteRange = maxRouteRange;
}

Vehicle::~Vehicle() {
	id = NULL;
	capacity = NULL;
	load = NULL;
	delete &originDepot;
	routeRange = NULL;
	maxRouteRange = NULL;
	for (int i = 0; i < route.size(); i++) {
		Customer* ptr = &route[i];
		delete ptr;
	}
}

bool Vehicle::vehicleAvailable(Customer customer) {
	if (this->load + customer.demand > this->capacity) {

		return false;

	}

	int x1, y1, x2, y2;
	float extraDistance;

	x2 = customer.x;
	y2 = customer.y;

	if (this->route.empty()) {
		x1 = this->originDepot.x;
		y1 = this->originDepot.y;
	}
	else {
		x1 = this->route.back().x;
		y1 = this->route.back().y;
	}

	extraDistance = distanceBetweenCoordinates(x1, y1, x2, y2);

	if (this->routeRange + extraDistance > maxRouteRange) {
		return false;
	}
	return true;
}

SolutionInstance::SolutionInstance(std::vector<Depot> depots){

	int i, j, numDepots, vehicleId, depotVehicleCount, depotMaxRouteRange,
		depotMaxVehicleCapacity;

	vehicleId = 0;
	numDepots = depots.size();
	for (i = 0; i < numDepots; i++) {

		depotVehicleCount = depots[i].vehicleCount;
		depotMaxRouteRange = depots[i].maxRouteRange;
		depotMaxVehicleCapacity = depots[i].maxVehicleCapacity;

		for (j = 0; j < depotVehicleCount; j++) {

			Vehicle* vehicle = new Vehicle(vehicleId, depotMaxRouteRange, depotMaxVehicleCapacity, depots[i]);
			vehicleList.push_back(*vehicle);
			vehicleId++;
		}
	}
}

void SolutionInstance::generateRandomSolution(std::vector<Customer> customers) {
	bool vehicleAvailable;
	int i, customerCount, vehicleCount, randomVehicleNumber;
	customerCount = customers.size();
	vehicleCount = vehicleList.size();

	for (i = 0; i < customerCount; i++) {

		randomVehicleNumber = rand() % vehicleCount;
		vehicleAvailable = vehicleList[randomVehicleNumber].vehicleAvailable(customers[i]);

		if (vehicleAvailable) {
			vehicleList[randomVehicleNumber].route.push_back(customers[i]);
		}
		else {
			i--;
		}
	}
}

float distanceBetweenCoordinates(int x1, int y1, int x2, int y2) {
	float distance;
	distance = sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) );
	return distance;
}

void testRand() {
	int v1;
	int v2;
	v1 = rand() % 100;
	v2 = rand() % 100;
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
}
