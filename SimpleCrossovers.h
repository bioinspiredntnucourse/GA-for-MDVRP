#pragma once
#include "solutionInstance.h"
#include <math.h>

struct InsertEval {
	float insertCost; //low number is good

	int insertIndex;
	Vehicle *insertInVehicle;
	Customer insertCustomer;
};

void _removeCustomerFromInstance(Customer &cust, SolutionInstance &inst);

void _removeRouteFromInstance(Vehicle route, SolutionInstance &inst);

float _evaluateInsertion(Customer &c, Vehicle &v, int insertPos);

InsertEval _findBestInsertionInPath(Customer &cust, Vehicle &insertInRoute);

InsertEval _findBestInsertionInAllWithEqualStartDepot(Customer &cust, SolutionInstance &inst, int startDepot);

InsertEval _findBestInsertionInAll(Customer &cust, SolutionInstance &inst);

void _doInsert(InsertEval eval);

vector<InsertEval> _bcrcInsertAllIntoBestRoutesWithEqualStartDepot(Vehicle &insertFrom, SolutionInstance &insertInto, int startDepot);

void _insertAllIntoBestOfAllRoute(Vehicle &insertFrom, SolutionInstance &insertInto);

void BestCostRouteCrossover(SolutionInstance &inst1, SolutionInstance &inst2);

