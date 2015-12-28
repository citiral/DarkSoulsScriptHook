#pragma once

#include "DSPlayer.h"
#include "luna.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class DSLuaPlayer
{
public:
	DSLuaPlayer(DSPlayer* player);
	DSLuaPlayer(lua_State* L);
	~DSLuaPlayer();

	//wrapped functions
	int getBasePointer(lua_State* L);
	int getBasePointer2(lua_State* L);

	static const char className[];
	static const char tableName[];
	static const Luna<DSLuaPlayer>::RegType Register[];
private:
	DSPlayer* _player;
};