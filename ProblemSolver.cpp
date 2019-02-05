#include "ProblemSolver.h"

float ProblemSolver::CalculateFitness(SolutionInstance *solutionInstance) {
	int i;
	float fitness;
	fitness = 0;
	for (i = 0; i < solutionInstance->vehicleList.size(); i++) {
		fitness += solutionInstance->vehicleList[i].routeRange;
	}
	return fitness;
}

void ProblemSolver::Evaluate(vector<SolutionInstance*> *population, vector<float>* evaluation) {
	int i;
	int solutionFitness;
	for (i = 0; i < population->size(); i++) {

		(*population)[i]->fitness = this->CalculateFitness((*population)[i]);
	}
}