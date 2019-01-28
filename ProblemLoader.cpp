#include "ProblemLoader.h"
#include <iostream>
#include <fstream>



ProblemLoader::ProblemLoader()
{
}


ProblemLoader::~ProblemLoader()
{
}

Problem ProblemLoader::Load(string filename) {
	ifstream inFile;
	string line;

	inFile.open("..\\data_files\\Data Files\\p01");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	while (inFile >> line) {
		cout << line;
	}

	inFile.close();

	Problem p;
	return p;
}
