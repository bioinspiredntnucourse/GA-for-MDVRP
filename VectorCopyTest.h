#pragma once
#include <vector>
#include "solutionInstance.h"
#include "ProblemLoader.h"

using namespace std;

inline void CopyVectorTest() {
	Problem p = LoadProblem("data_files\\Data Files\\p01");

	SolutionInstance a(p);
	a.generateRandomSolution(p);

	cout << "routeRange 1: a " << a.vehicleList[0].routeRange << endl;

	SolutionInstance b = a;
	SolutionInstance c = a;

	b.fitness = 500;
	c.fitness = 234;

	cout << "fitness: b " << b.fitness << " c " << c.fitness << endl;

	b.vehicleList[0].routeRange = 30;
	c.vehicleList[0].routeRange = 4000;

	cout << "routeRange 1: a " << a.vehicleList[0].routeRange << " b " << b.vehicleList[0].routeRange << " c " << c.vehicleList[0].routeRange << endl;

	b.vehicleList = a.vehicleList;
	c.vehicleList = a.vehicleList;

	b.vehicleList[0].routeRange = 30;
	c.vehicleList[0].routeRange = 4000;

	cout << "routeRange after copy: a " << a.vehicleList[0].routeRange << " b " << b.vehicleList[0].routeRange << " c " << c.vehicleList[0].routeRange << endl;

}