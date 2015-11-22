#pragma once

#include <fstream>
/*
#pragma data_seg (".d3d9_shared")
std::fstream output;
#pragma data_seg ()*/

std::fstream output;
void initOutput()
{
	output.open("./debug.txt", std::ios_base::out);
}