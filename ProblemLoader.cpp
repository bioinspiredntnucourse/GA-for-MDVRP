#pragma once

#include "ProblemLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ProblemStructures.h"

Problem LoadProblem(string filename) {
	vector<Depot> depots;
	vector<Customer> customers;

	ifstream inFile;
	string line;

	inFile.open(filename);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	//read first line
	int maxVehiclesAtDepot;
	int customerCount;
	int depotCount;

	getline(inFile, line);
	std::istringstream lineStream(line);

	lineStream >> maxVehiclesAtDepot >> customerCount >> depotCount;

	depots = vector<Depot>(depotCount);
	customers = vector<Customer>(customerCount);

	//the next lines contain some depot info
	int routeMaxDuration;
	int vehicleMaxLoad;
	for (unsigned int i = 0; i < depotCount; ++i) {
		getline(inFile, line);
		std::istringstream lineStream(line);
		lineStream >> routeMaxDuration >> vehicleMaxLoad;

		depots[i].depotId = i;
		depots[i].vehicleCount = maxVehiclesAtDepot;
		depots[i].maxRouteRange = routeMaxDuration;
		depots[i].maxVehicleCapacity = vehicleMaxLoad;
	}

	//the next lines contain customer info
	int customerId;
	int xCoord, yCoord;
	int serviceDuration;
	int customerDemand;

	for (unsigned int i = 0; i < customerCount; ++i) {
		getline(inFile, line); //retrieving next line, and only using some of the data in it
		std::istringstream lineStream(line);

		lineStream >> customerId >> xCoord >> yCoord >> serviceDuration >> customerDemand;

		customers[i].customerNumber = customerId;
		customers[i].id = customerId;
		customers[i].x = xCoord;
		customers[i].y = yCoord;
		customers[i].demand = customerDemand;
		customers[i].serviceDuration = serviceDuration;
	}

	//the last lines also contains depot info
	int fileid;
	for (unsigned int i = 0; i < depotCount; ++i) {
		getline(inFile, line); //retrieving next line, and only using some of the data in it
		std::istringstream lineStream(line);

		lineStream >> fileid >> xCoord >> yCoord;

		depots[i].id = fileid;
		depots[i].x = xCoord;
		depots[i].y = yCoord;
	}
	inFile.close();

	Problem p;
	p.filename = filename;
	p.customers = customers;
	p.depots = depots;
	return p;
}
