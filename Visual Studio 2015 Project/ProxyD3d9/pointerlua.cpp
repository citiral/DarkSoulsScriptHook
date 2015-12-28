extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <Windows.h>
}
#include "pointerlua.h"

int lua_makePointer(lua_State* l)
{
	int val = luaL_checknumber(l, 1);

	lua_pushlightuserdata(l, (void*)val);

	return 1;
}

int lua_addPointer(lua_State* l)
{
	char* ptr = (char*)lua_touserdata(l, 1);
	int val = luaL_checknumber(l, 2);

	lua_pushlightuserdata(l, ptr + val);

	return 1;
}

int lua_tointPointer(lua_State* l)
{
	void* ptr = lua_touserdata(l, 1);

	lua_pushnumber(l, (unsigned int)ptr);

	return 1;
}

template<class T>
int lua_writeNumeric(lua_State* l)
{
	T* ptr = (T*)lua_touserdata(l, 1);
	T val = (T)lua_tonumber(l, 2);

	*ptr = val;

	return 0;
}

template<class T>
int lua_readNumeric(lua_State* l)
{
	T* ptr = (T*)lua_touserdata(l, 1);

	lua_pushnumber(l, *ptr);

	return 1;
}

int lua_writePtr(lua_State* l)
{
	void** ptr = (void**)lua_touserdata(l, 1);
	void* val = (void*)lua_touserdata(l, 2);

	*ptr = val;

	return 0;
}

int lua_readPtr(lua_State* l)
{
	void** ptr = (void**)lua_touserdata(l, 1);

	lua_pushlightuserdata(l, *ptr);

	return 1;
}

int lua_basePtr(lua_State* l)
{
	lua_pushlightuserdata(l, GetModuleHandle(nullptr));

	return 1;
}

luaL_Reg pointerFuncs[] = {
	{ "make", lua_makePointer },
	{ "add", lua_addPointer },
	{ "toint", lua_tointPointer },

	{ "writei32", lua_writeNumeric<int> },
	{ "writei16", lua_writeNumeric<short> },
	{ "writei8", lua_writeNumeric<char> },
	
	{ "writeu32", lua_writeNumeric<unsigned int> },
	{ "writeu16", lua_writeNumeric<unsigned short> },
	{ "writeu8", lua_writeNumeric<unsigned char> },
	
	{ "writef64", lua_writeNumeric<float> },
	{ "writef32", lua_writeNumeric<double> },
	
	{ "readi32", lua_readNumeric<int> },
	{ "readi16", lua_readNumeric<short> },
	{ "readi8", lua_readNumeric<char> },
	
	{ "readu32", lua_readNumeric<unsigned int> },
	{ "readu16", lua_readNumeric<unsigned short> },
	{ "readu8", lua_readNumeric<unsigned char> },

	{ "readf64", lua_readNumeric<double> },
	{ "readf32", lua_readNumeric<float> },

	{ "writeptr", lua_writePtr },
	{ "readptr", lua_readPtr },

	{ "base", lua_basePtr },

	0
};

void registerPointer(lua_State* l)
{
	//make an input table
	lua_newtable(l);
	luaL_setfuncs(l, pointerFuncs, 0);
	lua_setglobal(l, "ptr");
}