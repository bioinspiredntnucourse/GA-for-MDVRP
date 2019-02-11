#pragma once

#include "SwapStartMutation.h"
#include "ProblemSolver.h"
#include "ProblemLoader.h"
#include "output.h"

void SwapStartCrossoverTest() {
	Problem p = LoadProblem("data_files\\Data Files\\p01");
	SolutionInstance inst(p);
	inst.generateRandomSolution(p);

	SolutionInstance newInst = SwapStartDepotMutation(inst);

	cout << "init" << endl;
	printSolutionRoute(inst);
	cout << "after" << endl;
	printSolutionRoute(newInst);
}