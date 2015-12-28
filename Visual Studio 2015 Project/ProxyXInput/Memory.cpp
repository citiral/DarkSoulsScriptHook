#pragma once

#include "Memory.h"
#include <Windows.h>

void writeByte(int offset, unsigned char byte)
{
	*((char*)GetModuleHandle("DarkSoulsII.exe") + offset) = byte;
}

Code* allocateCode(int size, unsigned char* code)
{
	unsigned char* data = new unsigned char[size];

	for (int i = 0; i < size; i++) {
		data[i] = code[i];
	}

	return (Code*)data;
}