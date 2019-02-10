#pragma once
#include "ProblemSolver.h"

void ProblemSolver::SolveMdvrpWithGa(const Problem &problem) {
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
		children = Crossover(parents);
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

		if (i % 50 == 0) {
			PlotGenerations(generationBest);
			DrawSolutionInstance(this->problem, generationBest.back());
		}
	}

	DrawSolutionInstance(this->problem, generationBest.back());
	PlotGenerations(generationBest);
}