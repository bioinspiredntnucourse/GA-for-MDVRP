#include "SwapStartMutation.h"

/*
swaps start depots of two routes with a possibility
implemented by swaping all customers in two routes, without actually changing the originDepot
*/
SolutionInstance SwapStartDepotMutation(SolutionInstance &_inst) {
	SolutionInstance inst = _inst;
	//choose two random paths
	Vehicle *v1_p = &inst.vehicleList[rand() % inst.vehicleList.size()];
	Vehicle *v2_p = &inst.vehicleList[rand() % inst.vehicleList.size()];

	Vehicle v1 = *v1_p; // make a copy of v1 so the customers here arent actually changed
	v1_p->route = v2_p->route; // set v1 route to that of v2
	v1_p->endDepot = v2_p->endDepot; //swap depots
	v1_p->load = v2_p->load; //swap load

	v2_p->route = v1.route; //set v2 to the old route of v1
	v2_p->endDepot = v1.endDepot;
	v2_p->load = v1.load;

	return inst;
}