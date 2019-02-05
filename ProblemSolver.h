#pragma once

#include "ProblemStructures.h"
#include "solutionInstance.h"
#include "output.h"

#include <iostream>

using namespace std;

class ProblemSolver {
private:
	//algorithm parameters
	Problem *problem;

	//control
	bool running = true;

public:
	int populationSize;

	inline void SolveMdvrpWithGa(Problem *problem) {
		this->problem = problem;

		//declare
		vector<SolutionInstance*> population = vector<SolutionInstance*>();
		vector<SolutionInstance*> parents = vector<SolutionInstance*>();
		vector<float> evaluations = vector<float>();

		
		//start
		InitializePopulation(&population);

		for (unsigned int i = 0; i < population.size(); i++) {
			cout << population[i]->fitness << endl;
			DrawSolutionInstance(*this->problem, *population[i]);
		}
		deleteSolutionInstances(&population);

		return;

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
	void deleteSolutionInstances(vector<SolutionInstance*>* instances) {
		for (unsigned int i = 0; i < instances->size(); i++) {
			delete instances->at(i);
		}
	}

	//GA flow
	void InitializePopulation(vector<SolutionInstance*> *population);

	//choose individuals and cross them
	void PopulationCrossover(vector<SolutionInstance*> *population, vector<float>* evaluations);
	//performing a crossover on a single individul
	SolutionInstance* CrossoverMutation(SolutionInstance* instance);

	//choose individuals and mutate them
	void PopulationMutate(vector<SolutionInstance*> *population, vector<float>* evaluations);
	SolutionInstance* Mutate(SolutionInstance* instance);

	//fill "evaluations" based on fitness of "instances"
	void Evaluate(vector<SolutionInstance*> *population, vector<float>* evaluations);

	//manipulate the population given the evaluations
	void SelectNextGeneration(vector<SolutionInstance*> *population, vector<float>* evaluations);


	//---utilities---
	SolutionInstance* GenerateRandomSolution(vector<Customer> customers);
};