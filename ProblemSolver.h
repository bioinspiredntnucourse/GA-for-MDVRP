#pragma once

#include "ProblemStructures.h"

class ProblemSolver
{
public:
	ProblemSolver();
	~ProblemSolver();

	void SolveMdvrpWithGa(Problem &problem);
};

