#pragma once

#include "SimpleCrossovers.h"
#include "ProblemLoader.h"
#include "output.h"

typedef SolutionInstance SI;

SolutionInstance genRandInst(Problem p) {
	SolutionInstance inst(p);
	inst.GenerateInitialSolution(p);
	return inst;
}

void println(Vehicle &v) {
	cout << "Vehicle, id: " << v.id << " start: " << v.originDepot.depotId << " end: " << v.endDepot.depotId
		<< " customers: ";
	for (auto &cust : v.route) {
		cout << cust.customerNumber << " ";
	}
	cout << endl;
}
void println(string s) {
	cout << s << endl;
}

void removeCustomerFromInstaceTest(Problem p) {
	//test removing of values
	SI si1 = genRandInst(p);
	SI si2 = genRandInst(p);

	//remove route 0 from inst1 from inst2
	Vehicle chooseVehicle = si1.vehicleList[0];
	_removeRouteFromInstance(chooseVehicle, si2);
	//check if route is existing in inst2
	for (auto &chosenCust : chooseVehicle.route) {

		//check all customers in inst2
		for (auto &vehicle2 : si2.vehicleList) {
			for (auto &cust2 : vehicle2.route) {
				if (cust2.customerNumber == chosenCust.customerNumber) {
					throw invalid_argument("customers not removed in the right way");
				}
			}
		}

	}
	cout << "PASSED: removeCustomerFromInstaceTest" << endl;
}

void bcrcInsertAllInRouteTest(Problem p) {
	println("bcrcInsertAllInRouteTest");

	SI si1 = genRandInst(p);
	SI si2 = genRandInst(p);

	//choose path to insert from
	Vehicle vfrom = si1.vehicleList[0];
	
	println("---BEFORE----");
	println("vehicle from");
	println(vfrom);
	println("vehicle into");
	printSolutionRoute(si2);

	_removeRouteFromInstance(vfrom, si2);

	println("---AFTER DELETION----");
	println("vehicle from");
	println(vfrom);
	println("vehicle into");
	printSolutionRoute(si2);

	_bcrcInsertAllIntoBestRoutesWithEqualStartDepot(vfrom, si2, 0);

	println("---AFTER----");
	println("vehicle from");
	println(vfrom);
	println("vehicle into");
	printSolutionRoute(si2);
}

void BestCostRouteCrossoverTest() {

	Problem p = LoadProblem("data_files\\Data Files\\p01");

	removeCustomerFromInstaceTest(p);

	bcrcInsertAllInRouteTest(p);

	SI inst1 = genRandInst(p);
	SI inst2 = genRandInst(p);
	SI inst1_old = inst1;
	SI inst2_old = inst2;

	BestCostRouteCrossover(inst1, inst2);


	println("inst1 before");
	printSolutionRoute(inst1_old);
	println("inst1 after");
	printSolutionRoute(inst1);

	println("inst2 before");
	printSolutionRoute(inst2_old);
	println("inst2 after");
	printSolutionRoute(inst2);
}