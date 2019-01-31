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
		vector<SolutionInstance*> population = vector<SolutionInstance*>(populationSize);
		vector<float> evaluations = vector<float>(populationSize);
		
		//start
		InitializePopulation(&population);
		Evaluate(&population, &evaluations);

		int i = 0;
		while (running) {
			PopulationCrossover(&population, &evaluations);
			PopulationMutate(&population, &evaluations);
			SelectNextGeneration(&population, &evaluations);

			if (i++ >= 100)
				running = false;
		}
	}

	//GA flow
	void InitializePopulation(vector<SolutionInstance*> *population);

	//choose individuals and cross them
	void PopulationCrossover(vector<SolutionInstance*> *population, vector<float>* evaluations);
	//performing a crossover on a single individul
	SolutionInstance* CrossoverMutation(SolutionInstance* instance);

	//choose individuals and mutate them
	vector<SolutionInstance> PopulationMutate(vector<SolutionInstance*> *population, vector<float>* evaluations);
	SolutionInstance* Mutate(SolutionInstance* instance);

	//fill "evaluations" based on fitness of "instances"
	void Evaluate(vector<SolutionInstance*> *population, vector<float>* evaluations);

	//manipulate the population given the evaluations
	void SelectNextGeneration(vector<SolutionInstance*> *population, vector<float>* evaluations);


	//utilities
	SolutionInstance* GenerateRandomSolution(vector<Customer> customers);
};