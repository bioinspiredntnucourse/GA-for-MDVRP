#pragma once
#include <vector>
#include "solutionInstance.h"
#include "ProblemLoader.h"

using namespace std;

inline void CopyVectorTest() {
	Problem p = LoadProblem("data_files\\Data Files\\p01");

	SolutionInstance a(p);
	SolutionInstance b = a;
	SolutionInstance c = a;

	b.fitness = 500;
	c.fitness = 234;

	cout << "fitness: b " << b.fitness << " c " << c.fitness << endl;

	b.vehicleList[0].maxRouteRange = 30;
	c.vehicleList[0].maxRouteRange = 4000;

	cout << "routeRange: b " << b.vehicleList[0].routeRange << " c " << c.vehicleList[0].routeRange << endl;

}