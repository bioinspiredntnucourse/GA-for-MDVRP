#pragma once

#include "solutionInstance.h"
#include "ProblemStructures.h"

#include <sstream>
#include <string>
#include <iostream>

void makeSolutionFile() {
	std::ostringstream os;
	os << "You" << 5 << "are" << 7;
	std::string s = os.str();
	std::cout << s;
}