#pragma once

#include "luna.h"
#include "DS2Player.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class DS2LuaPlayer
{
public:
	DS2LuaPlayer(DS2Player* player);
	DS2LuaPlayer(lua_State* L);
	~DS2LuaPlayer();

	//wrapped functions
	//int getHealth(lua_State* L);
	//int setHealth(lua_State* L/*int health*/);
	int getBasePointer(lua_State* L);
	int getBasePointer2(lua_State* L);

	static const char className[];
	static const char tableName[];
	static const Luna<DS2LuaPlayer>::RegType Register[];

private:
	DS2Player* _player;
};

