#pragma once

#include "solutionInstance.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <string>

Vehicle::Vehicle(int id, int capacity, Depot originDepot) {
	this->id = id;
	this->load = 0;
	this->capacity = capacity;
	this->originDepot = originDepot;
	this->routeRange = 0;
}

Vehicle::~Vehicle() {
	this->id = NULL;
	this->capacity = NULL;
	this->load = NULL;
	//delete &originDepot;
	//delete &endDepot;
	this->routeRange = NULL;
	this->maxRouteRange = NULL;
	/*
	for (int i = 0; i < this->route.size(); i++) {
		Customer* ptr = &this->route[i];
		delete ptr;
	}
	*/
}

bool Vehicle::vehicleAvailable(Customer customer) {
	if (this->load + customer.demand > this->capacity) {
		return false;
	}
	else {
		return true;
	}
}

float Vehicle::calculateDistance2Customer(Customer customer) {

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
	extraDistance = roundf(extraDistance* 100) / 100;
	return extraDistance;
}

void Vehicle::addCustomer2VehicleRoute(Customer customer) {
	float extraDistance;
	extraDistance = this->calculateDistance2Customer(customer);

	this->route.push_back(customer);
	this->routeRange = extraDistance + this->routeRange;
	this->load = customer.demand + this->load;
}

float distanceBetween(Location &loc1, Location &loc2) {
	return distanceBetweenCoordinates(loc1.x, loc1.y, loc2.x, loc2.y);
}
void Vehicle::RecalculateRouteDistance() {

	//if there are no customers, set the distance to 0, because this path isnt concidered
	if (route.size() == 0) {
		routeRange = 0; // distanceBetween(originDepot, endDepot);
		return;
	}

	float totDist = 0;
	totDist += distanceBetween(originDepot, route[0]);
	for (unsigned int i = 1; i < route.size(); i++) {
		totDist += distanceBetween(route[i - 1], route[i]);
	}
	totDist += distanceBetween(route.back(), endDepot);
	this->routeRange = totDist;
}

SolutionInstance::SolutionInstance(Problem problem){

	std::vector<Depot> depots;
	depots = problem.depots;

	int l;

	this->fitness = -1;

	int i, j, numDepots, vehicleId, depotVehicleCount, depotMaxRouteRange,
		depotMaxVehicleCapacity;

	vehicleId = 0;
	numDepots = depots.size();
	for (i = 0; i < numDepots; i++) {

		depotVehicleCount = depots[i].vehicleCount;
		depotMaxVehicleCapacity = depots[i].maxVehicleCapacity;

		for (j = 0; j < depotVehicleCount; j++) {
			Vehicle vehicle = Vehicle(vehicleId, depotMaxVehicleCapacity, depots[i]);
			this->vehicleList.push_back(vehicle);
			vehicleId++;
		}
	}
}

void SolutionInstance::generateRandomSolution(Problem problem) {
	std::vector<Customer> customers;
	customers = problem.customers;

	bool vehicleAvailable;
	int i, j, customerCount, vehicleCount, randomVehicleNumber, randomDepotNumber;
	customerCount = customers.size();
	vehicleCount = vehicleList.size();

	for (i = 0; i < customerCount; i++) {

		randomVehicleNumber = rand() % vehicleCount;
		vehicleAvailable = vehicleList[randomVehicleNumber].vehicleAvailable(customers[i]);

		if (vehicleAvailable) {
			vehicleList[randomVehicleNumber].addCustomer2VehicleRoute(customers[i]);
		}
		else {
			i--;
		}
	}

	for (j = 0; j < vehicleList.size(); j++) {
		randomDepotNumber = rand() % problem.depots.size();
		vehicleList[j].endDepot = problem.depots[randomDepotNumber];
		//std::cout << vehicleList[j].endDepot.depotId << std::endl;
	}
	
}

void SolutionInstance::GenerateInitialSolution(Problem problem) {
	bool vehicleAvailable, insertedValue;
	int i, j, k, vehicleNumber, currentSize;
	float distance;
	vector<float> shortestDistances;
	vector<Depot> closestDepots;
	for (i = 0; i < problem.customers.size(); i++) {
		closestDepots.clear();
		shortestDistances.clear();
		for (j = 0; j < problem.depots.size(); j++) {
			insertedValue = false;
			distance = distanceBetweenCoordinates(problem.depots[j].x, problem.depots[j].y, problem.customers[i].x, problem.customers[i].y);
			if (closestDepots.size() == 0) {
				closestDepots.push_back(problem.depots[j]);
				shortestDistances.push_back(distance);
			}
			else{
				currentSize = closestDepots.size();
				for (k = 0; k < currentSize; k++) {
					if (distance < shortestDistances[k]) {
						shortestDistances.insert(shortestDistances.begin() + k, distance);
						closestDepots.insert(closestDepots.begin() + k, problem.depots[j]);
						insertedValue = true;
					}
				}
				if (!insertedValue) {
					shortestDistances.push_back(distance);
					closestDepots.push_back(problem.depots[j]);
				}
			}
		}
		vehicleAvailable = false;
		for (j = 0; j < closestDepots.size(); j++) {
			if (vehicleAvailable == true) {
				break;
			}
			for (k = 0; k < closestDepots[j].vehicleCount; k++) {
				vehicleNumber = (closestDepots[j].depotId)*(closestDepots[j].vehicleCount) + k;
				vehicleAvailable = vehicleList[vehicleNumber].vehicleAvailable(problem.customers[i]);
				if (vehicleAvailable) {
					vehicleList[vehicleNumber].addCustomer2VehicleRoute(problem.customers[i]);
					break;
				}
			}
		}
	}
	for (i = 0; i < vehicleList.size(); i++) {
		vehicleList[i].endDepot = vehicleList[i].originDepot;
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
