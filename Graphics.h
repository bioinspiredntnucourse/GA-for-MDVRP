#pragma once
#include <string>

using namespace std;

inline void DrawSolution(string problemFilename, string solutionFilename) {
	string pyfile = "drawSolution.py";

	string pypath = "./python/";
	string python = "py";
	string pyinput = problemFilename + " " + solutionFilename;

	string initCommand = "start /b CMD.exe /k";
	string terminating = "";

	string command = initCommand + " " + python + " " + pypath + pyfile + " " + pyinput;
	//command = "ls -l &";
	cout << command << endl;
	system(command.c_str());
}