#pragma once
#include "solutionInstance.h"
#include <math.h>

vector<SolutionInstance> PartiallyMappedCrossover(const SolutionInstance &inst) {
	//get two random paths, might be the same
	Vehicle v1 = inst.vehicleList[rand() % inst.vehicleList.size()];
	Vehicle v2 = inst.vehicleList[rand() % inst.vehicleList.size()];

	//find and use the minimal length of the two paths
	//int pathLen = min();

	//get two random points within path1, the second after the first
	// + 2 to include the depots
	int p1 = rand() % (v1.route.size() + 2);
	int p2 = (rand() % (v2.route.size() + 2 - p1)) + p1;

	Vehicle c1v1 = v1;
	//Vehicle c1v2 = v2;

	if (p1 == 0) {
		c1v1.originDepot = v1.originDepot;
	}
	//for (int i = 0; i < v1.)

	SolutionInstance child1 = inst;
	SolutionInstance child2 = inst;
}


void _removeCustomerFromInstance(Customer &cust, SolutionInstance &inst) {
	for (int vehicleInd = 0; vehicleInd < inst.vehicleList.size(); vehicleInd++) {
		//get the route of the vehicle
		vector<Customer> *route = &inst.vehicleList[vehicleInd].route;

		for (int custInd = 0; custInd < route->size(); custInd++) {

			if ((*route)[custInd].customerNumber == cust.customerNumber) {
				//erase the customer if it is equal to the given
				route->erase(route->begin() + custInd);
			}
		}
	}
}

void _removeRouteFromInstance(Vehicle route, SolutionInstance &inst) {
	for (int i = 0; i < route.route.size(); i++) {
		//for each customer in the route
		Customer *routeCust = &route.route[i];

		//go through 
		_removeCustomerFromInstance(*routeCust, inst);
	}
}


void BestCostRouteCrossover(SolutionInstance &inst1, SolutionInstance &inst2) {
	//suggestion: randomly select by origin depot or endDepot

	int depotCount = 4; //make dynamic

	//find a random start depot, the end depot ay be whatever
	//works if all depots are equally present:
	int startDepotId = rand() % depotCount; // inst1.vehicleList[rand() % inst1.vehicleList.size()].originDepot.depotId;

	//choose a random route from each inst with valid startDepot
	Vehicle *route1, *route2;
	do {
		route1 = & inst1.vehicleList[rand() % inst1.vehicleList.size()];
	} while (route1->originDepot.depotId != startDepotId);
	do {
		route2 = & inst2.vehicleList[rand() % inst2.vehicleList.size()];
	} while (route1->originDepot.depotId != startDepotId);
	 
	//remove route1 from inst2 and route2 from inst1
	_removeRouteFromInstance(*route1, inst2);
	_removeRouteFromInstance(*route2, inst1);

	//try to insert the customers from the route1 at different locations in inst2 where originDepot is valid
	//and evaluate

}

