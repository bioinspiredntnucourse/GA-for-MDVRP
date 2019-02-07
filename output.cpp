#pragma once
#include "output.h"

int outputDrawSolutionFilenumber = 0;

void DrawSolutionInstance(Problem &problem, SolutionInstance &solutionInstance) {
	//string filename = "./generatedToDraw.res";
	string filename = "./z_generatedToDraw" + to_string(outputDrawSolutionFilenumber++) + ".res";
	cout << "filename: " << filename << endl;
	makeSolutionFile(solutionInstance, problem, filename);
	DrawSolution("\"" + problem.filename + "\"", filename);
}