#pragma once

#include "luna.h"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Game;

class GameLua
{
public:
	GameLua(Game* ds2);
	GameLua(lua_State* l);
	
	~GameLua();

	int writeInt(lua_State* l/*, void* ptr, int offset, int data*/);
	int readInt(lua_State* l/*, void* ptr, int offset*/);
	int writePtr(lua_State* l/*, void* ptr, int offset, void* data*/);
	int readPtr(lua_State* l/*, void* ptr, int offset*/);
	int writeShort(lua_State* l/*, void* ptr, int offset, int data*/);
	int readShort(lua_State* l/*, void* ptr, int offset*/);
	int writeByte(lua_State* l/*, void* ptr, int offset, unsigned char data*/);
	int readByte(lua_State* l/*, void* ptr, int offset*/);
	int pressKey(lua_State* l/*, uint key*/);
	int baseAddress(lua_State* l);
	int isNull(lua_State* l/*, void* ptr */);
	int toPtr(lua_State* l/*, long ptr */);
	int fromPtr(lua_State* l/*, void* ptr*/);
	int addPtr(lua_State* l/*, void* ptr, int add*/);

	static const char className[];
	static const char tableName[];
	static const Luna<GameLua>::RegType Register[];

private:
	Game* _game;
};

