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


		for (unsigned int i = 0; i < population.size(); i++) {
			cout << population[i].fitness << endl;
			DrawSolutionInstance(this->problem, population[i]);
		}

		return;

		evaluations = Evaluate(population);

		int i = 0;
		while (running) {
			parents = ChooseParents(population, evaluations);
			children = ParentsCrossover(parents);
			mutatedChildren = MutateChildren(children);
			
			//add mutated children to the population
			population.insert(population.end(), mutatedChildren.begin(), mutatedChildren.end());

			evaluations = Evaluate(population);

			population = SelectNextGeneration(population, evaluations);
			evaluations = Evaluate(population);


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
	SolutionInstance CrossoverMutation(SolutionInstance instance);

	vector<SolutionInstance> MutateChildren(vector<SolutionInstance> children);
	SolutionInstance Mutate(SolutionInstance solutionInstance);

	//fill "evaluations" based on fitness of "instances"
	vector<float> Evaluate(vector<SolutionInstance> population);
	float CalculateFitness(SolutionInstance &solutionInstance);

	vector<SolutionInstance> Tournaments(vector<SolutionInstance> population, vector<float> evaluations);
	//manipulate the population given the evaluations
	vector<SolutionInstance> SelectNextGeneration(vector<SolutionInstance> population, vector<float> evaluations);

	vector<SolutionInstance> Replicate(vector<SolutionInstance> winners, int populationSize);

};