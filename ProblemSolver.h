#pragma once

#include "ProblemStructures.h"
#include "solutionInstance.h"

class ProblemSolver {
private:
	Problem problem;

	//algorithm parameters
	int populationSize;
	int crossoverProbability;
	int tournamentSize;
	float mutationProbability;

	//control
	bool running = true;

public:

	inline void SolveMdvrpWithGa(Problem &problem) {

		//declare
		vector<SolutionInstance> population;
		
		//start
		population = InitializePopulation(population);
		population = Evaluate(population);

		int i = 0;
		while (running) {
			Crossover(population);
			MutateChildren(population);
			SelectNextGeneration(population);

			if (i++ >= 100)
				running = false;
		}
	}

	//GA flow
	vector<SolutionInstance> InitializePopulation(vector<SolutionInstance> population);

	//choose individuals and cross them
	vector<SolutionInstance> Crossover(vector<SolutionInstance> population);
	//performing a crossover on a single individul
	SolutionInstance IndividualCrossover(SolutionInstance instance);

	//choose individuals and mutate them
	vector<SolutionInstance> MutateChildren(vector<SolutionInstance> population);
	SolutionInstance MutateChild(SolutionInstance solutionInstance);

	//fill "evaluations" based on fitness of "instances"
	vector<SolutionInstance> Evaluate(vector<SolutionInstance> population);
	float CalculateFitness(SolutionInstance& solutionInstance);

	vector<SolutionInstance> Tournaments(vector<SolutionInstance> population);
	//manipulate the population given the evaluations
	void SelectNextGeneration(vector<SolutionInstance> population);

	vector<SolutionInstance> Replicate(vector<SolutionInstance> winners, int populationSize);


	//utilities
	SolutionInstance GenerateRandomSolution(vector<Customer> customers);
	void swapRouteSectionsAtIndexN(vector<Customer>& route1, vector<Customer>& route2, int N);
};