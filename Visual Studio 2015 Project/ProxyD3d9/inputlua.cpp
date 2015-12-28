extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "inputlua.h"
#include "Input.h"

int lua_isPressed(lua_State* l)
{
	int key = luaL_checknumber(l, 1);
	
	lua_pushboolean(l, input::getKeyPressed(key));

	return 1;
}

int lua_getState(lua_State* l)
{
	int key = luaL_checknumber(l, 1);

	lua_pushnumber(l, input::getKeyState(key));

	return 1;
}

luaL_Reg inputFuncs[] = {
	{ "isPressed", lua_isPressed },
	{ "getState", lua_getState },
	0
};

void registerInput(lua_State* l)
{
	//make an input table
	lua_newtable(l);
	luaL_setfuncs(l, inputFuncs, 0);
	lua_setglobal(l, "input");
}