#pragma once
#include "ProblemSolver.h"
#include "solutionInstance.h"
#include <iostream>

vector<SolutionInstance> ProblemSolver::InitializePopulation() {
	vector<SolutionInstance> population;// = vector<SolutionInstance>(this->populationSize);
	population.reserve(populationSize);

	for (unsigned int i = 0; i < populationSize; i++) {
		//SolutionInstance *solinst = GenerateRandomSolution(this->problem->customers);
		SolutionInstance sol(this->problem);
		sol.generateRandomSolution(this->problem);

		population.push_back(sol);
	}

	std::cout << "population should be: " << populationSize << " population is: " << population.size() << std::endl;
	return population;
}

//choose individuals to cross
vector<SolutionInstance> ProblemSolver::ChooseParents(vector<SolutionInstance> population, vector<float> evaluations) {
	return vector<SolutionInstance>();
}
vector<SolutionInstance> ProblemSolver::ParentsCrossover(vector<SolutionInstance> parents) {
	return vector<SolutionInstance>();
}
//manipulate the population given the evaluations
vector<SolutionInstance> ProblemSolver::SelectNextGeneration(vector<SolutionInstance> population) {
	vector<SolutionInstance> currentSolutions;

	currentSolutions.reserve(populationSize);

	//put populationSize number of instances in our currentVectors
	for (unsigned int i = 0; i < populationSize; i++) {
		currentSolutions.push_back(population[i]);
	}

	//of the remaining, replace the better ones with the existing bad ones in currentVector
	for (unsigned int i = populationSize; i < population.size(); i++) {
		for (unsigned int j = 0; j < currentSolutions.size(); j++) {
			if (population[i].fitness < currentSolutions[j].fitness) {
				currentSolutions[j] = population[i];
				break;
			}
		}
	}

	return currentSolutions;
}


vector<SolutionInstance> ProblemSolver::MutateChildren(vector<SolutionInstance> children) {
	int i;
	float randomScore;
	vector<SolutionInstance> mutatedChildren;
	mutatedChildren.reserve(children.size());
	
	for (i = 0; i < children.size(); i++) {
		randomScore = (rand() % 100) / 100;
		std::cout << randomScore << std::endl; //PRINT! REMOVE AFTER
		if (randomScore > (1 - this->mutationProbability)) {
			mutatedChildren.push_back( Mutate(children[i]) );
		}
	}

	return mutatedChildren;
}


SolutionInstance ProblemSolver::Mutate(SolutionInstance target) {
	//create a copy of the target
	SolutionInstance solutionInstance = target;
	solutionInstance.vehicleList = target.vehicleList; //copies the values in the first vector to the second, if the first assignment only vopies a reference

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

	return solutionInstance;
}


vector<SolutionInstance> ProblemSolver::Evaluate(vector<SolutionInstance> population) {
	int i;
	int solutionFitness;
	vector<SolutionInstance> evaluatedInstances;
	for (i = 0; i < population.size(); i++) {
		solutionFitness = this->CalculateFitness(population[i]);
		population[i].fitness = solutionFitness;
		evaluatedInstances.push_back(population[i]);
	}
	return evaluatedInstances;
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