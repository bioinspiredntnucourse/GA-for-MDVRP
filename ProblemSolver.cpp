#include "ProblemSolver.h"
#include <iostream>

vector<SolutionInstance> ProblemSolver::Crossover(vector<SolutionInstance> copys) {
	int i;
	float randomScore;
	for (i = 0; i < copys.size(); i++) {
		randomScore = (rand() % 100) / 100;
		std::cout << randomScore << std::endl; //PRINT! REMOVE AFTER
		if (randomScore > (1 - this->crossoverProbability)) {
			copys[i] = IndividualCrossover(copys[i]);
		}
	}
}

SolutionInstance ProblemSolver::IndividualCrossover(SolutionInstance instance) {

}

vector<SolutionInstance> ProblemSolver::MutateChildren(vector<SolutionInstance> children) {
	int i;
	float randomScore;
	vector<SolutionInstance> mutatedChildren;
	
	for (i = 0; i < children.size(); i++) {
		mutatedChildren[i] = MutateChild(children[i]);
	}
	return mutatedChildren;
}

SolutionInstance ProblemSolver::MutateChild(SolutionInstance solutionInstance) {
	int i, j, randomCustomerNumber, randomVehicleNumber;
	float randomScore;
	Customer tempCustomer;
	for (i = 0; i < solutionInstance.vehicleList.size(); i++) {
		for (j = 0; j < solutionInstance.vehicleList[i].route.size(); j++) {
			randomScore = float((rand() % 100)) / float(100);
			if (randomScore > (1 - this->mutationProbability)) {
				randomVehicleNumber = rand() % solutionInstance.vehicleList.size();
				randomCustomerNumber = rand() % solutionInstance.vehicleList[randomVehicleNumber].route.size();
				tempCustomer = solutionInstance.vehicleList[i].route[j];
				solutionInstance.vehicleList[i].route[j] = solutionInstance.vehicleList[randomVehicleNumber].route[randomCustomerNumber];
				solutionInstance.vehicleList[randomVehicleNumber].route[randomCustomerNumber] = tempCustomer;
			}
		}
	}
	return solutionInstance;
}

vector<float> ProblemSolver::Evaluate(vector<SolutionInstance> population) {
	int i;
	int solutionFitness;
	vector<float> evaluation;
	for (i = 0; i < population.size(); i++) {
		solutionFitness = this->CalculateFitness(population[i]);
		population[i].fitness = solutionFitness;
		evaluation.push_back(solutionFitness);
	}
	return evaluation;
}


float ProblemSolver::CalculateFitness(SolutionInstance& solutionInstance) {
	int i;
	float fitness;
	fitness = 0;
	for (i = 0; i < solutionInstance.vehicleList.size(); i++) {
		fitness += solutionInstance.vehicleList[i].routeRange;
	}
	return fitness;
}

vector<SolutionInstance> ProblemSolver::Tournaments(vector<SolutionInstance> population, vector<float> evaluations) {
	int i, j, numWinners;
	int tournamentLeaderScore;
	vector<SolutionInstance> winners;

	if (population.size() % tournamentSize > 0) {
		numWinners = (population.size() / tournamentSize) + 1;
	}
	else {
		numWinners = (population.size() / tournamentSize);
	}
	//vector<SolutionInstance> winners(tournamentSize);
	for (i = 0; i < numWinners; i++) {
		tournamentLeaderScore = 9999999999;
		for (j = 0; j < tournamentSize; j++) {
			if (evaluations[(i*numWinners) + j] < tournamentLeaderScore) {
				winners.push_back(population[(i*numWinners) + j]);
			}
		}
	}
	return winners;
}

vector<SolutionInstance> ProblemSolver::Replicate(vector<SolutionInstance> winners, int populationSize) {
	int i, j, copyPerParent;
	vector<SolutionInstance> winnerCopys;
	copyPerParent = tournamentSize;
	for (i = 0; i < winners.size(); i++) {
		for (j = 0; j < copyPerParent; j++) {
			winnerCopys.push_back(winners[i]);
			if (winnerCopys.size() >= populationSize) {
				break;
			}
		}
	}
	return winnerCopys;
}

