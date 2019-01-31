#pragma once
#include <string>

using namespace std;

inline void DrawSolution(string problemFilename, string solutionFilename) {
	string pyfile = "drawSolution.py";

	string pypath = "./python/";
	string python = "py";
	string pyinput = problemFilename + " " + solutionFilename;

	string command = python + " " + pypath + pyfile + " " + pyinput;
	system(command.c_str());
}