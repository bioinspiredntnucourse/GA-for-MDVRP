#include "ProblemLoaderTest.h"
#include "ProblemLoader.h"
#include <iostream>


using namespace std;

void ProblemLoaderTest() {
	Problem p = LoadProblem("data_files\\Data Files\\p01");

	ProblemToStream(p, cout);

	string ds;
	cin >> ds;
}