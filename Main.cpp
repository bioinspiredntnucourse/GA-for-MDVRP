#pragma once
#include <iostream>
#include <string>
#include "ProblemStructures.h"
#include "solutionInstance.h"

#include "ProblemLoaderTest.h"

#include "output.h"

int main() {
	/*
	Customer cust;
	Depot dep;
	cust.id = 1;
	cust.x = 1;
	cust.y = 2;
	cust.customerNumber = 0;

	dep.depotId = 4;
	dep.maxRouteRange = 2;
	std::cout << dep.depotId << std::endl;

	//DUMMY DATA
	Depot testDepot;
	testDepot.id = 9;
	testDepot.x = 5;
	testDepot.y = 7;
	testDepot.depotId = 0;
	testDepot.vehicleCount = 2;
	testDepot.maxRouteRange = 20;
	testDepot.maxVehicleCapacity = 3;

	Customer testCustomer1;
	testCustomer1.id = 0;
	testCustomer1.x = 0;
	testCustomer1.y = 0;
	testCustomer1.customerNumber = 0;
	testCustomer1.serviceDuration = 0;
	testCustomer1.demand = 1;

	Customer testCustomer2;
	testCustomer2.id = 1;
	testCustomer2.x = 7;
	testCustomer2.y = 2;
	testCustomer2.customerNumber = 1;
	testCustomer2.serviceDuration = 0;
	testCustomer2.demand = 2;

	Problem testProblem;
	testProblem.depots.push_back(testDepot);
	testProblem.customers.push_back(testCustomer1);
	testProblem.customers.push_back(testCustomer2);

	makeSolutionFile();

	std::string exit;
	std::cin >> exit;
	*/

	ProblemLoaderTest();

	return 0;
}