#include "ProblemSolver.h"
#include <iostream>

//vector<>

void ProblemSolver::PopulationMutate(vector<SolutionInstance> population) {
	int i;
	float randomScore;
	
	for (i = 0; i < population.size(); i++) {
		randomScore = (rand() % 100) / 100;
		std::cout << randomScore << std::endl; //PRINT! REMOVE AFTER
		if (randomScore > (1 - this->mutationProbability)) {
			Mutate(population[i]);
		}
	}
}


void ProblemSolver::Mutate(SolutionInstance solutionInstance) {
	int randomRouteNumber_1, randomRouteNumber_2, 
		randomCustomerOnRoute_1, randomCustomerOnRoute_2,
		randomDepotNumber;
	Customer tempCustomer;

	randomRouteNumber_1 = rand() % solutionInstance.vehicleList.size();
	randomCustomerOnRoute_1 = rand() % (solutionInstance.vehicleList[randomRouteNumber_1].route.size() + 1);
	
	if (randomCustomerOnRoute_1 == solutionInstance.vehicleList[randomRouteNumber_1].route.size()) { // Change endDepots
		randomDepotNumber = rand() % (this->problem.depots.size());
		solutionInstance.vehicleList[randomRouteNumber_1].endDepot = this->problem.depots[randomDepotNumber];
		std::cout << "DEPOT MUTATION" << std::endl;
	}
	else { // Swap single random customer
		randomCustomerOnRoute_1 = rand() % solutionInstance.vehicleList[randomRouteNumber_1].route.size();
		randomRouteNumber_2 = rand() % solutionInstance.vehicleList.size();
		randomCustomerOnRoute_2 = rand() % (solutionInstance.vehicleList[randomRouteNumber_2].route.size());
		tempCustomer = solutionInstance.vehicleList[randomRouteNumber_1].route[randomCustomerOnRoute_1];
		solutionInstance.vehicleList[randomRouteNumber_1].route[randomCustomerOnRoute_1] = solutionInstance.vehicleList[randomRouteNumber_2].route[randomCustomerOnRoute_2];
		solutionInstance.vehicleList[randomRouteNumber_2].route[randomCustomerOnRoute_2] = tempCustomer;
	}
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

