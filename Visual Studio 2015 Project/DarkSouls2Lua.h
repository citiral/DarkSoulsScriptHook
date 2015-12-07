#pragma once

#include "luna.h"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class DarkSouls2;

class DarkSouls2Lua
{
public:
	DarkSouls2Lua(DarkSouls2* ds2);
	DarkSouls2Lua(lua_State* l);
	
	~DarkSouls2Lua();

	int writeInt(lua_State* l/*, void* ptr, int offset, int data*/);
	int readInt(lua_State* l/*, void* ptr, int offset*/);
	int writePtr(lua_State* l/*, void* ptr, int offset, void* data*/);
	int readPtr(lua_State* l/*, void* ptr, int offset*/);
	int writeShort(lua_State* l/*, void* ptr, int offset, int data*/);
	int readShort(lua_State* l/*, void* ptr, int offset*/);
	int pressKey(lua_State* l/*, uint key*/);
	int baseAddress(lua_State* l);
	int isNull(lua_State* l/*, void* ptr */);
	int toPtr(lua_State* l/*, long ptr */);
	int fromPtr(lua_State* l/*, void* ptr*/);
	int addPtr(lua_State* l/*, void* ptr, int add*/);

	static const char className[];
	static const char tableName[];
	static const Luna<DarkSouls2Lua>::RegType Register[];

private:
	DarkSouls2* _ds2;
};

