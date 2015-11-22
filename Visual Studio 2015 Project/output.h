#pragma once

#include <iostream>

#ifdef _DEBUG
	#define D_ERR(x) std::cerr << "ERROR in " << __FILE__ << " at line " << __LINE__ << ": " << x << "\n";
	#define D_WAR(x) std::cerr << "WARNING: " << x << "\n";
	#define D_OUT(x) std::cout << x << "\n";
#else
	#define D_ERR(x)
	#define D_WAR(x)
	#define D_OUT(x)
#endif

#define R_ERR(x) std::cerr << "ERROR in " << __FILE__ << " at line " << __LINE__ << ": " << x << "\n";
#define R_WAR(x) std::cerr << "WARNING: " << x << "\n";
#define R_OUT(x) std::cout << x << "\n";