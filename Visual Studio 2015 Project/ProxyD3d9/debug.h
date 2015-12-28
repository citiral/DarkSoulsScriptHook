#pragma once
#include "lua.h"
#include <stdio.h>
#include <string.h>
#include <sstream>

extern FILE* pFile;

void printString(const char* str);
void flushDebugFile();

template<class T>
void printValue(T val) {
	std::stringstream ss;
	ss << val;
	std::string str = ss.str();
	printString(str.c_str());
}



//int l_printString(lua_State* L);