#pragma once

#include "Graphics.h"

inline void GraphicsTest() {
	//the path ./data_files/Data Files/ is implicit if no other path is given (handeled in the python script
	DrawSolution("p01", "p01.res");
	//use the surrounding quotationmarks if the path containes spaces
	DrawSolution("\"./data_files/Data Files/p03\"", "\"./data_files/Solution Files/p03.res\"");
}