#pragma once
#include <iostream>
#include <string>

#include <sstream>
#include <iterator>
#include <ctime>
#include <cstdlib>

#include "ProblemStructures.h"
#include "ProblemLoader.h"

//#include "output.h"

#include "ProblemSolver.h"

#include "VectorCopyTest.h"

#include "CrossoverTest.h"

int main() {
	srand(time(NULL));
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
	*/

	/*
	Problem p = LoadProblem("data_files\\Data Files\\p01");

	//ProblemToStream(p, cout);
	
	SolutionInstance sol(p);
	sol.generateRandomSolution(p);
	ProblemSolver problemSolver;
	sol.fitness = problemSolver.CalculateFitness(sol);

	makeSolutionFile(sol, p, "solutionFile.txt");

	string problemfile = "\"./data_files/Data Files/p01\"";
	string solutionfile = "./solutionFile.txt";

	DrawSolution(problemfile, solutionfile);

		CopyVectorTest();
	*/

	/*

	*/

	Problem p = LoadProblem("data_files\\Data Files\\p01");

	ProblemSolver ps;
	ps.iterations = 1000;
	ps.populationSize = 100;
	ps.crossoverProbability = 0.0;
	ps.mutationProbability = 0.02;
	ps.idealMutationProbability = 0.00;
	ps.endDepotMutationProbability = 0.0;
	ps.randomTournamentWinnerProbability = 0.0;
	ps.tournamentSize = 5;

	ps.SolveMdvrpWithGa(p);

	//BestCostRouteCrossoverTest();

	std::string exit;
	std::cin >> exit;



	return 0;
}