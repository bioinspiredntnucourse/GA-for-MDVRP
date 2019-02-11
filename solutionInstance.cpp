#pragma once

#include "solutionInstance.h"
#include "simpleCrossovers.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <map>

#include <string>

Vehicle::Vehicle(int id, int capacity, Depot originDepot) {
	this->id = id;
	this->load = 0;
	this->capacity = capacity;
	this->originDepot = originDepot;
	this->routeRange = 0;
	if (originDepot.maxRouteRange == 0) {
		this->maxRouteRange = float(numeric_limits<float>::max());
	}
	else {
		this->maxRouteRange = originDepot.maxRouteRange;
	}
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
	float distance;
	if (this->route.size() != 0) {
		distance = distanceBetween(customer, this->route.back());
	}
	else {
		distance = distanceBetween(customer, this->originDepot);
	}
	if ((this->load + customer.demand <= this->capacity) && (this->routeRange + distance <= this->maxRouteRange) ) {
		return true;
	}
	else {
		return false;
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
	//extraDistance = roundf(extraDistance* 100) / 100;
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

void SolutionInstance::GenerateInitialSolution3(Problem problem) {
	float distance;
	map<float, Depot> tempDepotDistance;
	vector<map<float, Depot> > depotDistances;

	//Assign all customer2depot distances in map(sorted)
	for (int i = 0; i < problem.customers.size(); i++) {
		tempDepotDistance.clear();
		for (int j = 0; j < problem.depots.size(); j++) {
			distance = distanceBetweenCoordinates(problem.customers[i].x, problem.customers[i].y, problem.depots[j].x, problem.depots[j].y);
			while (tempDepotDistance.find(distance) != tempDepotDistance.end()) {
				distance = distance + 0.0001;
			}
			tempDepotDistance[distance] = problem.depots[j];
		}
		depotDistances.push_back(tempDepotDistance);
	}


	bool vehicleAvailable, newAssignmentChosen, insertSuccessfull;
	int vehicleNumber, tempCustomerNumber, numCustomerServed;
	float longestDistance2SecondDepot;
	InsertEval tempInsertEval;
	vector<bool> customerServed;

	for (int i = 0; i < problem.customers.size(); i++) {
		customerServed.push_back(false);
	}
	//std::cout << (++depotDistances[0].begin())->second.depotId << std::endl;
	numCustomerServed = 0;
	while (numCustomerServed < customerServed.size()) {
		for (int i = 0; i < problem.depots.size(); i++) {
			newAssignmentChosen = false;
			longestDistance2SecondDepot = 0;
			for (int j = 0; j < depotDistances.size(); j++) {
				if (depotDistances[j].begin()->second.depotId == problem.depots[i].depotId && !customerServed[j] && numCustomerServed < customerServed.size()) {
					if ((++depotDistances[j].begin())->first > longestDistance2SecondDepot) {
						longestDistance2SecondDepot = (++depotDistances[j].begin())->first;
						tempCustomerNumber = j;
						newAssignmentChosen = true;
					}
				}
			}

			if (newAssignmentChosen) {
				insertSuccessfull = false;
				vehicleAvailable = false;
				for (int j = 0; j < problem.depots[i].vehicleCount; j++) {
					vehicleNumber = (problem.depots[i].depotId)*(problem.depots[i].vehicleCount) + j;
					vehicleAvailable = vehicleList[vehicleNumber].vehicleAvailable(problem.customers[tempCustomerNumber]);
					if (vehicleAvailable) {
						tempInsertEval = _findBestInsertionInPath(problem.customers[tempCustomerNumber], vehicleList[vehicleNumber]);
						insertSuccessfull = _doInsert(tempInsertEval);
						if (!insertSuccessfull) {
							std::cout << "_doInsert NOT SUCCESSFULL! THIS SHOULD NOT HAPPEN" << std::endl;
						}

						customerServed[tempCustomerNumber] = true;
						numCustomerServed += 1;
						break;
						//std::cout << numCustomerServed << std::endl;
					}
				}
				if (!vehicleAvailable) {
					depotDistances[tempCustomerNumber].erase(longestDistance2SecondDepot);
				}
			}
		}
	}

	for (int i = 0; i < vehicleList.size(); i++) {
		vehicleList[i].endDepot = vehicleList[i].originDepot;
	}
	//PrintMap
	/*for (int i = 0; i < depotDistances.size(); i++){
		std::cout << "CustomerNumber: " << i << std::endl;
		for (map<float, Depot>::iterator it = depotDistances[i].begin(); it != depotDistances[i].end(); ++it) {
			std::cout << it->first << " => " << it->second.depotId << '\n';
		}
	}*/
}

void SolutionInstance::GenerateInitialSolution2(Problem problem) {
	float distance;
	map<float, Depot> tempDepotDistance;
	vector<map<float, Depot> > depotDistances;

	//Assign all customer2depot distances in map(sorted)
	for (int i = 0; i < problem.customers.size(); i++) {
		tempDepotDistance.clear();
		for (int j = 0; j < problem.depots.size(); j++) {
			distance = distanceBetweenCoordinates(problem.customers[i].x, problem.customers[i].y, problem.depots[j].x, problem.depots[j].y);
			while (tempDepotDistance.find(distance) != tempDepotDistance.end()) {
				distance = distance + 0.0001;
			}
			tempDepotDistance[distance] = problem.depots[j];
		}
		depotDistances.push_back(tempDepotDistance);
	}


	bool vehicleAvailable, newAssignmentChosen;
	int vehicleNumber, tempCustomerNumber, numCustomerServed;
	float longestDistance2SecondDepot;
	vector<bool> customerServed;


	for (int i = 0; i < problem.customers.size(); i++) {
		customerServed.push_back(false);
	}
	//std::cout << (++depotDistances[0].begin())->second.depotId << std::endl;
	numCustomerServed = 0;
	while (numCustomerServed < customerServed.size()) {
		for (int i = 0; i < problem.depots.size(); i++) {
			newAssignmentChosen = false;
			longestDistance2SecondDepot = 0;
			for (int j = 0; j < depotDistances.size(); j++) {
				if (depotDistances[j].begin()->second.depotId == problem.depots[i].depotId && !customerServed[j] && numCustomerServed < customerServed.size()) {
					if ((++depotDistances[j].begin())->first > longestDistance2SecondDepot) {
						longestDistance2SecondDepot = (++depotDistances[j].begin())->first;
						tempCustomerNumber = j;
						newAssignmentChosen = true;
					}
				}
			}

			if (newAssignmentChosen) {
				vehicleAvailable = false;
				for (int j = 0; j < problem.depots[i].vehicleCount; j++) {
					vehicleNumber = (problem.depots[i].depotId)*(problem.depots[i].vehicleCount) + j;
					vehicleAvailable = vehicleList[vehicleNumber].vehicleAvailable(problem.customers[tempCustomerNumber]);
					if (vehicleAvailable) {
						vehicleList[vehicleNumber].addCustomer2VehicleRoute(problem.customers[tempCustomerNumber]);
						
						customerServed[tempCustomerNumber] = true;
						numCustomerServed += 1;
						break;
						//std::cout << numCustomerServed << std::endl;
					}
				}
				if (!vehicleAvailable) {
					depotDistances[tempCustomerNumber].erase(longestDistance2SecondDepot);
				}
			}
		}
	}

	for (int i = 0; i < vehicleList.size(); i++) {
		vehicleList[i].endDepot = vehicleList[i].originDepot;
	}
	//PrintMap
	/*for (int i = 0; i < depotDistances.size(); i++){
		std::cout << "CustomerNumber: " << i << std::endl;
		for (map<float, Depot>::iterator it = depotDistances[i].begin(); it != depotDistances[i].end(); ++it) {
			std::cout << it->first << " => " << it->second.depotId << '\n';
		}
	}*/
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
						break;
					}
				}
				if (!insertedValue) {
					shortestDistances.push_back(distance);
					closestDepots.push_back(problem.depots[j]);
				}
			}
		}
		//Printing SHortest Distance
		/*std::cout << "CustomerNumber:  "<< problem.customers[i].customerNumber << std::endl;
		for (j = 0; j < shortestDistances.size(); j++) {
			std::cout << shortestDistances[j] << "      ";
		}
		std::cout << std::endl;
		for (j = 0; j < closestDepots.size(); j++) {
		std::cout << closestDepots[j].depotId << "      ";
		}
		std::cout << std::endl;*/


		vehicleAvailable = false;
		for (j = 0; j < closestDepots.size(); j++) {
			if (vehicleAvailable == true) {
				break;
			}
			for (k = 0; k < closestDepots[j].vehicleCount; k++) {
				vehicleNumber = (closestDepots[j].depotId)*(closestDepots[j].vehicleCount) + k;
				vehicleAvailable = vehicleList[vehicleNumber].vehicleAvailable(problem.customers[i]);
				if (vehicleAvailable) {
					//std::cout << "vehicleNumber: " << vehicleNumber << "     depotId: " << closestDepots[j].depotId << "        load: " << vehicleList[vehicleNumber].load << "          customerId: " << problem.customers[i].customerNumber <<std::endl;
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
