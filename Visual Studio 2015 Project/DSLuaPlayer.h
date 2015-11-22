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
	int getHealth(lua_State* L);
	int setHealth(lua_State* L/*int health*/);

	static const char className[];
	static const char tableName[];
	static const Luna<DSLuaPlayer>::RegType Register[];
private:
	DSPlayer* _player;
};