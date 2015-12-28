#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

FILE* pFile = NULL;

void printString(const char* str) {
	if (pFile == NULL) {
		fopen_s(&pFile, "d3d9log.txt","w");
	}

	if (str != NULL && pFile != NULL) {
		fprintf(pFile, "%s\n", str);
		fflush(pFile);
	}
}

void flushDebugFile() {
	if (pFile != NULL) {
		//flushes the file and closes it just to be god damn completely sure
		fflush(pFile);
		fclose(pFile);
		pFile = NULL;
	}
}

/*int l_printString(lua_State* L) {
	const char* string = lua_tostring(L, -1);

	printString(string);

	return 0;
}*/