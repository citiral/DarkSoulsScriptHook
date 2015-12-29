#include "liblua.h"
#include "debug.h"
#include <sstream>

ModManager* _mm;

int lua_ptrToString(lua_State* l)
{
	void* ptr = lua_touserdata(l, 1);

	char buffer[64];
	sprintf_s(buffer, "%p", ptr);

	lua_pushstring(l, buffer);

	return 1;
}

int lua_printString(lua_State* l)
{
	const char* str = luaL_checkstring(l, 1);

	printString(str);
	
	return 0;
}

int lua_flushDebugFile(lua_State* l)
{
	flushDebugFile();
	return 0;
}

luaL_Reg libFuncs[] = {
	{ "ptrToString", lua_ptrToString },
	{ "printString", lua_printString },
	{ "flushDebugFile", lua_flushDebugFile },

	0
};

void registerLib(lua_State* l)
{
	//make an input table
	lua_newtable(l);
	luaL_setfuncs(l, libFuncs, 0);
	lua_setglobal(l, "lib");
}