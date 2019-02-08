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
	float crossoverProbability;
	int tournamentSize;
	float mutationProbability;
	int iterations;

	inline void SolveByRandom(const Problem &problem) {
		this->problem = problem;
		vector<SolutionInstance> population;

		SolutionInstance bestInstance(this->problem);
		bestInstance.fitness = 999999999;

		for (int i = 0; i < iterations; i++) {
			population = InitializePopulation();
			Evaluate(population);
			SolutionInstance inst = FindBestInstance(population);
			if (inst.fitness < bestInstance.fitness) {
				bestInstance = inst;
			}

			cout << "iteration " << i << endl;
		}
		DrawSolutionInstance(this->problem, bestInstance);
	}

	inline void SolveMdvrpWithGa(const Problem &problem) {
		this->problem = problem;

		//declare
		vector<SolutionInstance> population;
		vector<SolutionInstance> parents;
		vector<SolutionInstance> children;
		vector<SolutionInstance> mutatedChildren;
		vector<float> evaluations;

		//stats
		vector<SolutionInstance> generationBest;

		
		//start
		population = InitializePopulation();
		Evaluate(population);

		SolutionInstance bestInitInstance = FindBestInstance(population);
		DrawSolutionInstance(this->problem, bestInitInstance);

		int i = 0;
		while (running) {
			parents = ChooseParents(population);
			
			//printSolutionRoute(parents[7]);
			
			children = Crossover(parents);
			
			//printSolutionRoute(mutatedChildren[7]);
			
			mutatedChildren = MutateChildren(children);
			
			//evaluate only the newly generated children here
			//Evaluate(children);


			//add mutated children to the population
			population.insert(population.end(), mutatedChildren.begin(), mutatedChildren.end());

			Evaluate(population);

			population = SelectNextGeneration(population);
			Evaluate(population);

			cout << "iteration " << i << endl;
			generationBest.push_back(FindBestInstance(population));

			if (i++ >= iterations)
				running = false;

			if (i % 10 == 0) {
				PlotGenerations(generationBest);
				DrawSolutionInstance(this->problem, generationBest.back());
			}
		}

		DrawSolutionInstance(this->problem, generationBest.back());
		PlotGenerations(generationBest);
	}

	inline SolutionInstance FindBestInstance(vector<SolutionInstance> instances) {
		if (instances.size() == 0) throw invalid_argument("no instencesin vector");

		float lowestFitness = instances[0].fitness;
		int lowestFitnessIndex = 0;

		for (int i = 1; i < instances.size(); i++) {
			if (instances[i].fitness < lowestFitness) {
				lowestFitness = instances[i].fitness;
				lowestFitnessIndex = i;
			}
		}

		return instances[lowestFitnessIndex];
	}
	inline void DrawSolutions(vector<SolutionInstance> solutions) {
		for (int i = 0; i < solutions.size(); i++) {
			DrawSolutionInstance(this->problem, solutions[i]);
		}
	}

	//GA flow
	vector<SolutionInstance> InitializePopulation();

	//choose individuals to cross
	vector<SolutionInstance> ChooseParents(vector<SolutionInstance> population);
	vector<SolutionInstance> ParentsCrossover(vector<SolutionInstance> parents);

	vector<SolutionInstance> Crossover(vector<SolutionInstance> population);
	//performing a crossover on a single individul
	SolutionInstance IndividualCrossover(SolutionInstance instance);

	//choose individuals and mutate them
	vector<SolutionInstance> MutateChildren(vector<SolutionInstance> population);
	SolutionInstance MutateChild(SolutionInstance solutionInstance);

	//fill "evaluations" based on fitness of "instances"
	void Evaluate(vector<SolutionInstance> &population);
	float CalculateFitness(SolutionInstance& solutionInstance);

	vector<SolutionInstance> Tournaments(vector<SolutionInstance> population);
	//manipulate the population given the evaluations

	vector<SolutionInstance> Replicate(vector<SolutionInstance> winners, int populationSize);
	vector<SolutionInstance> SelectNextGeneration(vector<SolutionInstance> population);


	//utilities
	SolutionInstance GenerateRandomSolution(vector<Customer> customers);
	void swapRouteSectionsAtIndexN(vector<Customer>& route1, vector<Customer>& route2, int N);
};