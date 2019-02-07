#pragma once

#include "ProblemStructures.h"
#include "solutionInstance.h"
#include "output.h"

#include <iostream>

using namespace std;

class ProblemSolver {
private:
	//control
	Problem problem;
	bool running = true;


public:
	//algorithm parameters
	int populationSize;
	int crossoverProbability;
	int tournamentSize;
	float mutationProbability;

	inline void SolveMdvrpWithGa(const Problem &problem) {
		this->problem = problem;

		//declare
		vector<SolutionInstance> population;
		vector<SolutionInstance> parents;
		vector<SolutionInstance> children;
		vector<SolutionInstance> mutatedChildren;
		vector<float> evaluations;

		
		//start
		population = InitializePopulation();
		population = Evaluate(population);

		int i = 0;
		while (running) {

			parents = ChooseParents(population, evaluations);
			children = Crossover(parents);
			mutatedChildren = MutateChildren(children);
			
			//add mutated children to the population
			population.insert(population.end(), mutatedChildren.begin(), mutatedChildren.end());

			population = Evaluate(population);

			population = SelectNextGeneration(population);

			population = Evaluate(population);

			if (i++ >= 100)
				running = false;
		}


	}

	//GA flow
	vector<SolutionInstance> InitializePopulation();

	//choose individuals to cross
	vector<SolutionInstance> ChooseParents(vector<SolutionInstance> population, vector<float> evaluations);
	vector<SolutionInstance> ParentsCrossover(vector<SolutionInstance> parents);

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

	vector<SolutionInstance> Replicate(vector<SolutionInstance> winners, int populationSize);
	vector<SolutionInstance> SelectNextGeneration(vector<SolutionInstance> population);


	//utilities
	SolutionInstance GenerateRandomSolution(vector<Customer> customers);
	void swapRouteSectionsAtIndexN(vector<Customer>& route1, vector<Customer>& route2, int N);
};