#pragma once
#include "ProblemSolver.h"
#include "solutionInstance.h"



void ProblemSolver::InitializePopulation(vector<SolutionInstance*> *population) {
	for (unsigned int i = 0; i < populationSize; i++) {
		//SolutionInstance *solinst = GenerateRandomSolution(this->problem->customers);
		SolutionInstance *solinst = new SolutionInstance(*this->problem);
		solinst->generateRandomSolution(*this->problem);

		population->push_back(solinst);
	}
}


void ProblemSolver::PopulationCrossover(vector<SolutionInstance*> *population, vector<float>* evaluations) {

}

SolutionInstance* ProblemSolver::CrossoverMutation(SolutionInstance* instance) {
	SolutionInstance si(*this->problem);
	return &si;
}


void ProblemSolver::PopulationMutate(vector<SolutionInstance*> *population, vector<float>* evaluations) {

}



void ProblemSolver::Evaluate(vector<SolutionInstance*> *population, vector<float>* evaluations) {

}


void ProblemSolver::SelectNextGeneration(vector<SolutionInstance*> *population, vector<float>* evaluations) {

}