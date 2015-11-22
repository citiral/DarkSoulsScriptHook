#include "stdafx.h"
#include "DarkSouls2Lua.h"
#include "DarkSouls2.h"


DarkSouls2Lua::DarkSouls2Lua(DarkSouls2* ds2)
{
	_ds2 = ds2;
}


DarkSouls2Lua::DarkSouls2Lua(lua_State* l)
{
	D_OUT("Do not manually construct DS2 instances. (It just won't work)");
}

DarkSouls2Lua::~DarkSouls2Lua()
{

}

int DarkSouls2Lua::writeInt(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	int data = luaL_checkinteger(l, 4);

	_ds2->writeMemory<int>((char*)ptr + offset, &data);

	return 0;
}

int DarkSouls2Lua::readInt(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	int data;

	_ds2->readMemory<int>((char*)ptr + offset, &data);

	lua_pushnumber(l, data);
	return 1;
}

int DarkSouls2Lua::writeShort(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	short data = luaL_checkinteger(l, 4);

	_ds2->writeMemory<short>((char*)ptr + offset, &data);

	return 0;
}

int DarkSouls2Lua::readShort(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	short data;

	_ds2->readMemory<short>((char*)ptr + offset, &data);

	lua_pushnumber(l, data);
	return 1;
}

const char DarkSouls2Lua::className[] = "DarkSouls2";
const char DarkSouls2Lua::tableName[] = "DarkSouls2Table";
const Luna<DarkSouls2Lua>::RegType DarkSouls2Lua::Register[] = {
	{ "writeInt", &DarkSouls2Lua::writeInt },	
	{ "readInt", &DarkSouls2Lua::readInt },
	{ "writeShort", &DarkSouls2Lua::writeShort },
	{ "readShort", &DarkSouls2Lua::readShort },
	{ 0 }
};