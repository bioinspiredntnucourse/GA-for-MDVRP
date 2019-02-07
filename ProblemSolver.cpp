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
//performing a crossover on a single individul
SolutionInstance ProblemSolver::CrossoverMutation(SolutionInstance instance) {
	return SolutionInstance(this->problem);
}

//choose individuals and mutate them
vector<SolutionInstance> ProblemSolver::MutateChildren(vector<SolutionInstance> children) {
	return vector<SolutionInstance>();
}
SolutionInstance ProblemSolver::Mutate(SolutionInstance solutionInstance) {
	return SolutionInstance(this->problem);
}

//fill "evaluations" based on fitness of "instances"
vector<float> ProblemSolver::Evaluate(vector<SolutionInstance> population) {
	return vector<float>();
}
float ProblemSolver::CalculateFitness(SolutionInstance solutionInstance) {
	return 0;
}

vector<SolutionInstance> ProblemSolver::Tournaments(vector<SolutionInstance> population, vector<float> evaluations) {
	return vector<SolutionInstance>();
}
//manipulate the population given the evaluations
vector<SolutionInstance> ProblemSolver::SelectNextGeneration(vector<SolutionInstance> population, vector<float> evaluations) {
	return vector<SolutionInstance>();
}


/*
void ProblemSolver::PopulationMutate(vector<SolutionInstance*> *population) {
	int i;
	float randomScore;
	
	for (i = 0; i < population->size(); i++) {
		randomScore = (rand() % 100) / 100;
		std::cout << randomScore << std::endl; //PRINT! REMOVE AFTER
		if (randomScore > (1 - this->mutationProbability)) {
			Mutate((*population)[i]);
		}
	}
}

void ProblemSolver::Mutate(SolutionInstance* solutionInstance) {
	int randomRouteNumber_1, randomRouteNumber_2, 
		randomCustomerOnRoute_1, randomCustomerOnRoute_2,
		randomDepotNumber;
	Customer tempCustomer;

	randomRouteNumber_1 = rand() % solutionInstance->vehicleList.size();
	randomCustomerOnRoute_1 = rand() % (solutionInstance->vehicleList[randomRouteNumber_1].route.size() + 1);
	
	if (randomCustomerOnRoute_1 == solutionInstance->vehicleList[randomRouteNumber_1].route.size()) { // Change endDepots
		randomDepotNumber = rand() % (this->problem->depots.size());
		solutionInstance->vehicleList[randomRouteNumber_1].endDepot = this->problem->depots[randomDepotNumber];
		std::cout << "DEPOT MUTATION" << std::endl;
	}
	else { // Swap single random customer
		randomCustomerOnRoute_1 = rand() % solutionInstance->vehicleList[randomRouteNumber_1].route.size();
		randomRouteNumber_2 = rand() % solutionInstance->vehicleList.size();
		randomCustomerOnRoute_2 = rand() % (solutionInstance->vehicleList[randomRouteNumber_2].route.size());
		tempCustomer = solutionInstance->vehicleList[randomRouteNumber_1].route[randomCustomerOnRoute_1];
		solutionInstance->vehicleList[randomRouteNumber_1].route[randomCustomerOnRoute_1] = solutionInstance->vehicleList[randomRouteNumber_2].route[randomCustomerOnRoute_2];
		solutionInstance->vehicleList[randomRouteNumber_2].route[randomCustomerOnRoute_2] = tempCustomer;
	}
}

void ProblemSolver::Evaluate(vector<SolutionInstance*> *population, vector<float>* evaluation) {
	int i;
	int solutionFitness;
	for (i = 0; i < population->size(); i++) {
		solutionFitness = this->CalculateFitness((*population)[i]);
		(*population)[i]->fitness = solutionFitness;
		(*evaluation)[i] = solutionFitness;
	}
}

float ProblemSolver::CalculateFitness(SolutionInstance *solutionInstance) {
	int i;
	float fitness;
	fitness = 0;
	for (i = 0; i < solutionInstance->vehicleList.size(); i++) {
		fitness += solutionInstance->vehicleList[i].routeRange;
	}
	return fitness;
}

vector<SolutionInstance> ProblemSolver::Tournaments(vector<SolutionInstance*> *population, vector<float>* evaluations) {
	int i, j, numWinners;
	int tournamentLeaderScore;
	//vector<SolutionInstance> winners;

	if (population->size() % tournamentSize > 0) {
		numWinners = (population->size() / tournamentSize) + 1;
	}
	else {
		numWinners = (population->size() / tournamentSize);
	}
	vector<SolutionInstance> winners(tournamentSize, *this->problem);
	for (i = 0; i < numWinners; i++) {
		tournamentLeaderScore = 9999999999;
		for (j = 0; j < tournamentSize; j++) {
			if ((*evaluations)[(i*numWinners) + j] < tournamentLeaderScore) {
				winners[i] = *(*population)[(i*numWinners) + j];
			}
		}
	}
	return winners;
}

void ProblemSolver::PopulationCrossover(vector<SolutionInstance*> *population) {

}

void ProblemSolver::SelectNextGeneration(vector<SolutionInstance*> *population, vector<float>* evaluations) {

}
*/