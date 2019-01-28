#pragma once

#include "ProblemStructures.h";
#include <string>


using namespace std;

class ProblemLoader
{
public:
	ProblemLoader();
	~ProblemLoader();

	Problem Load(string filename);
};

