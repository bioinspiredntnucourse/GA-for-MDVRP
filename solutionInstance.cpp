#include "solutionInstance.h"
#include <stdlib.h>
#include <iostream>

Vehicle::Vehicle() {
	id = -1;
	capacity = -1;
	originDepot = -1;
	maxRouteDuration = -1;
}
Vehicle::Vehicle(int id, int maxRouteDuration, int capacity, Depot originDepot) {
	id = id;
	capacity = capacity;
	originDepot = originDepot;
	maxRouteDuration = maxRouteDuration;
}

Vehicle::~Vehicle() {
	id = NULL;
	capacity = NULL;
	delete &originDepot;
	maxRouteDuration = NULL;
	for (int i = 0; i < route.size(); i++) {
		Customer* ptr = &route[i];
		delete ptr;
	}
}

bool Vehicle::vehicleAvailable(Vehicle vehicle, Customer customer) {
	if (vehicle.route.empty) {

	}
}

SolutionInstance::SolutionInstance(std::vector<Depot> depots){

	int i, j, numDepots, vehicleId, depotVehicleCount, depotMaxRouteDuration,
		depotMaxVehicleCapacity;

	vehicleId = 0;
	numDepots = depots.size();
	for (i = 0; i < numDepots; i++) {

		depotVehicleCount = depots[i].vehicleCount;
		depotMaxRouteDuration = depots[i].maxRouteDuration;
		depotMaxVehicleCapacity = depots[i].maxVehicleCapacity;

		for (j = 0; j < depotVehicleCount; j++) {

			Vehicle* vehicle = new Vehicle(vehicleId, depotMaxRouteDuration, depotMaxVehicleCapacity, depots[i]);
			vehicleList.push_back(*vehicle);
			vehicleId++;
		}
	}
}

void SolutionInstance::generateRandomSolution(std::vector<Customer> customers) {
	Vehicle vehicle;
	int i, customerCount, vehicleCount, randomVehicleNumber;
	customerCount = customers.size();
	vehicleCount = vehicleList.size();

	for (i = 0; i < customerCount; i++) {
		randomVehicleNumber = rand() % vehicleCount;
		if (Vehicle::vehicleAvailable(vehicleList[randomVehicleNumber], customers[i])) {
			vehicleList[randomVehicleNumber].route.push_back()
		}
	}
}

void testRand() {
	int v1;
	int v2;
	v1 = rand() % 100;
	v2 = rand() % 100;
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
}
