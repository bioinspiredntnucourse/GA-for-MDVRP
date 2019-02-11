#pragma once

#include "ProblemStructures.h"
#include "solutionInstance.h"
#include "output.h"

#include <iostream>

using namespace std;

class ProblemSolver {
private:
	//control
	bool running = true;


public:
	Problem problem;

	//mutation stats
	int swapStartDepotMutations = 0;
	int changeEndDepotMutations = 0;
	int idealCustChangeMutations = 0;


	//algorithm parameters
	int populationSize;
	float crossoverProbability;
	int tournamentSize;
	float mutationProbability;
	float idealMutationProbability;
	float endDepotMutationProbability;
	float randomTournamentWinnerProbability;
	float swapStartDepotMutationProb;
	int iterations;

	//solver methods
	void SolveMdvrpWithGa(const Problem &problem);
	void SolveByRandom(const Problem &problem);

	vector<SolutionInstance> InitializePopulation();

	vector<SolutionInstance> ChooseParents(vector<SolutionInstance> population);

	vector<SolutionInstance> Crossover(vector<SolutionInstance> population);

	vector<SolutionInstance> MutateChildren(vector<SolutionInstance> population);




	SolutionInstance IndividualCrossover(SolutionInstance instance);
	SolutionInstance IdealReroutingMutation(SolutionInstance instance, int vehicleNumber, int customerNumber);
	SolutionInstance ChangeEndDepotMutation(SolutionInstance inst, int vehicleInd);
	SolutionInstance MutateChild(SolutionInstance solutionInstance);

	//fill "evaluations" based on fitness of "instances"
	void Evaluate(vector<SolutionInstance> &population);
	float CalculateFitness(SolutionInstance& solutionInstance);

	vector<SolutionInstance> Tournaments(vector<SolutionInstance> population);
	//manipulate the population given the evaluations

	vector<SolutionInstance> Replicate(vector<SolutionInstance> winners, int populationSize);
	vector<SolutionInstance> SelectNextGeneration(vector<SolutionInstance> population);


	//utilities
	//SolutionInstance GenerateInitialSolution(Problem problem);
	void swapRouteSectionsAtIndexN(vector<Customer>& route1, vector<Customer>& route2, int N);

	SolutionInstance FindBestInstance(vector<SolutionInstance> instances);
	void DrawSolutions(vector<SolutionInstance> solutions);

};
int loadAfterMutation(Vehicle vehicle, Customer currentCustomer, Customer newCustomer);

bool routeMutationValid(Vehicle vehicle, Customer currentCustomer, Customer newCustomer);
