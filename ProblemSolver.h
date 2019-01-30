#pragma once

#include "ProblemStructures.h"
#include "solutionInstance.h"

class ProblemSolver {
private:
	//algorithm parameters
	int populationSize;

	//control
	bool running = true;

public:

	inline void SolveMdvrpWithGa(Problem &problem) {

		//declare
		vector<SolutionInstance> population = vector<SolutionInstance>(populationSize);
		vector<SolutionInstance> newParents = vector<SolutionInstance>(populationSize);
		int parentCount;
		vector<float> evaluations = vector<float>(populationSize);


		//start
		InitializePopulation(&population);
		Evaluate(&population, &evaluations);

		while (running) {
			parentCount = SelectParents(&population, &newParents);
			Crossover()
		}
	}

	//GA flow
	void InitializePopulation(vector<SolutionInstance>* emptyPopulation);

	//
	int SelectParents(vector<SolutionInstance>* instances, vector<SolutionInstance>* parents);
	SolutionInstance Crossover(SolutionInstance instance1, SolutionInstance instance2);

	vector<SolutionInstance> SelectMutationTargets(vector<SolutionInstance> instances);
	SolutionInstance Mutate(SolutionInstance instnace);

	//fill "evaluations" based on fitness of "instances"
	void Evaluate(vector<SolutionInstance>* instances, vector<float>* evaluations);

	vector<SolutionInstance> SelectNextGeneration(vector<SolutionInstance> instances, vector<float> evaluations);

	//utilities
	SolutionInstance GenerateRandomSolution(vector<Customer> customers);
};