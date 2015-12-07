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

int DarkSouls2Lua::writePtr(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	void* data = lua_touserdata(l, 4);

	_ds2->writeMemory<void*>((char*)ptr + offset, &data);

	return 0;
}

int DarkSouls2Lua::readPtr(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	void* data;

	_ds2->readMemory<void*>((char*)ptr + offset, &data);

	lua_pushlightuserdata(l, data);
	return 1;
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

int DarkSouls2Lua::pressKey(lua_State * l)
{
	int key = luaL_checkinteger(l, 2);
	
	_ds2->pressKey(key);

	return 0;
}

int DarkSouls2Lua::baseAddress(lua_State * l)
{
	lua_pushlightuserdata(l, _ds2->getBaseAddress());

	return 1;
}

int DarkSouls2Lua::isNull(lua_State * l)
{
	void* ptr = lua_touserdata(l, 2);
	lua_pushboolean(l, ptr == nullptr);
	return 1;
}

int DarkSouls2Lua::toPtr(lua_State * l)
{
	long long val = luaL_checknumber(l, 2);
	lua_pushlightuserdata(l, (void*)val);
	return 1;
}

int DarkSouls2Lua::fromPtr(lua_State * l)
{
	void* val = lua_touserdata(l, 2);

	lua_pushnumber(l, (long long)val);
	return 1;
}

int DarkSouls2Lua::addPtr(lua_State * l)
{
	void* val = lua_touserdata(l, 2);
	long long add = luaL_checknumber(l, 3);

	lua_pushlightuserdata(l, ((char*)val) + add);
	return 1;
}

const char DarkSouls2Lua::className[] = "DarkSouls2";
const char DarkSouls2Lua::tableName[] = "DarkSouls2Table";
const Luna<DarkSouls2Lua>::RegType DarkSouls2Lua::Register[] = {
	{ "writeInt", &DarkSouls2Lua::writeInt },
	{ "readInt", &DarkSouls2Lua::readInt },
	{ "writePtr", &DarkSouls2Lua::writePtr },
	{ "readPtr", &DarkSouls2Lua::readPtr },
	{ "writeShort", &DarkSouls2Lua::writeShort },
	{ "readShort", &DarkSouls2Lua::readShort },
	{ "pressKey", &DarkSouls2Lua::pressKey },
	{ "baseAddress", &DarkSouls2Lua::baseAddress, },
	{ "isNull", &DarkSouls2Lua::isNull, },
	{ "toPtr", &DarkSouls2Lua::toPtr },
	{ "fromPtr", &DarkSouls2Lua::fromPtr },
	{ "addPtr", &DarkSouls2Lua::addPtr },
	{ 0 }
};