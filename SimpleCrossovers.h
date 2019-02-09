#pragma once
#include "solutionInstance.h"
#include <math.h>


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

struct InsertEval {
	float insertCost; //low number is good

	int insertIndex;
	Vehicle *insertInVehicle;
	Customer *insertCustomer;
};

//returns change in distance
//accepts insertPos int the range [0, v.size()] //that is one more than valid in v
float _evaluateInsertion(Customer &c, Vehicle &v, int insertPos) {
	if (insertPos < 0 || insertPos > v.route.size())
		throw invalid_argument("invalid insertPos");

	//insert pos is the index before the element at the given index, and after the last index
	float oldEval;
	float newEval;

	//if we insert at first position, it is between the first depot and first car
	if (insertPos == 0) {
		newEval = distanceBetween(v.originDepot, c) + distanceBetween(c, v.route[0]);
		oldEval = distanceBetween(v.originDepot, v.route[0]);
	}
	//and for the index 1 outside the path range
	else if (insertPos == v.route.size()) {
		newEval = distanceBetween(v.route[ v.route.size() -1 ], c) + distanceBetween(c, v.endDepot);
		oldEval = distanceBetween(v.route[v.route.size() - 1], v.endDepot);

	}
	//otherwise the index is inside the path
	else {
		newEval = distanceBetween(v.route[insertPos - 1], c) + distanceBetween(c, v.route[insertPos]);
		oldEval = distanceBetween(v.route[insertPos - 1], v.route[insertPos]);
	}
	return oldEval - newEval;
}

InsertEval _findBestInsertionInPath(Customer &cust, Vehicle &insertInRoute) {
	InsertEval bestEval;
	//generate a stupidly bad solution
	bestEval.insertCost = 99999999999;
	bestEval.insertCustomer = &cust;
	bestEval.insertInVehicle = &insertInRoute;
	bestEval.insertIndex = 0;

	if (insertInRoute.route.size() == 0) {
		return bestEval;
	}

	for (int i = 0; i < insertInRoute.route.size() +1; i++) {
		//test insertions from pos 0 to insertInRoute.size()
		float eval = _evaluateInsertion(cust, insertInRoute, i);
		//cout << "evaluation: " << eval << endl;

		if (eval < bestEval.insertCost) {
			bestEval.insertCost = eval;
			bestEval.insertIndex = i;
			bestEval.insertInVehicle = &insertInRoute;
			bestEval.insertCustomer = &cust;
		}

	}
	return bestEval;
}

InsertEval _findBestInsertionInAllWithEqualStartDepot(Customer &cust, SolutionInstance &inst, int startDepot) {
	//find best evaluations in each route
	vector<InsertEval> evals;
	for (auto &route : inst.vehicleList) {

		//if startDepot is right
		if (route.originDepot.depotId == startDepot) {

			//if there are no customers in a route, dont look at it
			if (route.route.size() != 0) {
				InsertEval eval = _findBestInsertionInPath(cust, route);
				evals.push_back(eval);
			}
		}
	}

	//choose the best
	InsertEval bestEval;
	bestEval.insertCost = 999999999;
	for (auto &eval : evals) {
		if (eval.insertCost < bestEval.insertCost) {
			bestEval = eval;
		}
	}
	return bestEval;
}

InsertEval _findBestInsertionInAll(Customer &cust, SolutionInstance &inst) {
	//find best evaluations in each route
	vector<InsertEval> evals;
	for (auto &route : inst.vehicleList) {

		//if there are no customers in a route, dont look at it
		if (route.route.size() != 0) {
			InsertEval eval = _findBestInsertionInPath(cust, route);
			evals.push_back(eval);
		}
	}

	//choose the best
	InsertEval bestEval;
	bestEval.insertCost = 999999999;
	for (auto &eval : evals) {
		if (eval.insertCost < bestEval.insertCost) {
			bestEval = eval;
		}
	}
	return bestEval;
}

void _doInsert(InsertEval eval) {
	vector<Customer> *r = &eval.insertInVehicle->route;

	//if we are at the index outside the vector, push
	if (eval.insertIndex == r->size()) {
		r->push_back(*eval.insertCustomer);
	}
	else {
		//inserts before the given index
		r->insert(r->begin() + eval.insertIndex, *eval.insertCustomer);
	}
}

//inserts the given vehicle customers from
void _bcrcInsertAllIntoBestRoutesWithEqualStartDepot(Vehicle &insertFrom, SolutionInstance &insertInto, int startDepot) {

	//find routes that have the same startDep

	for (int i = 0; i < insertFrom.route.size(); i++) {
		Customer insertCust = insertFrom.route[i];
		InsertEval eval = _findBestInsertionInAllWithEqualStartDepot(insertCust, insertInto, startDepot);
		_doInsert(eval);
	}
}

void _insertAllIntoBestOfAllRoute(Vehicle &insertFrom, SolutionInstance &insertInto) {

	//find routes that have the same startDep

	for (int i = 0; i < insertFrom.route.size(); i++) {
		Customer insertCust = insertFrom.route[i];
		InsertEval eval = _findBestInsertionInAll(insertCust, insertInto);
		_doInsert(eval);
	}
}


void BestCostRouteCrossover(SolutionInstance &inst1, SolutionInstance &inst2) {
	//suggestion: randomly select by origin depot or endDepot


	int depotCount = inst1.vehicleList[inst1.vehicleList.size() - 1].originDepot.depotId + 1;


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

	//get all paths that starts at the given depot
	_bcrcInsertAllIntoBestRoutesWithEqualStartDepot(*route1, inst2, startDepotId);
	_bcrcInsertAllIntoBestRoutesWithEqualStartDepot(*route2, inst1, startDepotId);
}


/*
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

*/