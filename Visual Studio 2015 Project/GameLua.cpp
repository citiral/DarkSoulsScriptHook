#include "stdafx.h"
#include "GameLua.h"
#include "DarkSouls2.h"


GameLua::GameLua(Game* game)
{
	_game = game;
}


GameLua::GameLua(lua_State* l)
{
	D_OUT("Do not manually construct DS2 instances. (It just won't work)");
}

GameLua::~GameLua()
{

}

int GameLua::writePtr(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	void* data = lua_touserdata(l, 4);

	_game->writeMemory<void*>((char*)ptr + offset, &data);

	return 0;
}

int GameLua::readPtr(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	void* data;

	_game->readMemory<void*>((char*)ptr + offset, &data);

	lua_pushlightuserdata(l, data);
	return 1;
}

int GameLua::writeInt(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	int data = luaL_checkinteger(l, 4);

	_game->writeMemory<int>((char*)ptr + offset, &data);

	return 0;
}

int GameLua::readInt(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	int data;

	_game->readMemory<int>((char*)ptr + offset, &data);

	lua_pushnumber(l, data);
	return 1;
}

int GameLua::writeShort(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	short data = luaL_checkinteger(l, 4);

	_game->writeMemory<short>((char*)ptr + offset, &data);

	return 0;
}

int GameLua::readShort(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	unsigned short data;

	_game->readMemory<unsigned short>((char*)ptr + offset, &data);
	
	lua_pushnumber(l, data);
	return 1;
}

int GameLua::writeByte(lua_State* l/*, void* ptr, int offset, int data*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checkinteger(l, 3);
	unsigned char data = luaL_checkinteger(l, 4);

	_game->writeMemory<unsigned char>((char*)ptr + offset, &data);

	return 0;
}

int GameLua::readByte(lua_State* l/*, void* ptr, int offset*/)
{
	void* ptr = lua_touserdata(l, 2);
	int offset = luaL_checknumber(l, 3);
	unsigned char data;

	_game->readMemory<unsigned char>((char*)ptr + offset, &data);
	
	lua_pushnumber(l, data);
	return 1;
}

int GameLua::pressKey(lua_State * l)
{
	int key = luaL_checkinteger(l, 2);
	
	_game->pressKey(key);

	return 0;
}

int GameLua::baseAddress(lua_State * l)
{
	lua_pushlightuserdata(l, _game->getBaseAddress());

	return 1;
}

int GameLua::isNull(lua_State * l)
{
	void* ptr = lua_touserdata(l, 2);
	lua_pushboolean(l, ptr == nullptr);
	return 1;
}

int GameLua::toPtr(lua_State * l)
{
	long long val = luaL_checknumber(l, 2);
	lua_pushlightuserdata(l, (void*)val);
	return 1;
}

int GameLua::fromPtr(lua_State * l)
{
	void* val = lua_touserdata(l, 2);

	lua_pushnumber(l, (long long)val);
	return 1;
}

int GameLua::addPtr(lua_State * l)
{
	void* val = lua_touserdata(l, 2);
	long long add = luaL_checknumber(l, 3);

	lua_pushlightuserdata(l, ((char*)val) + add);
	return 1;
}

const char GameLua::className[] = "DarkSouls2";
const char GameLua::tableName[] = "DarkSouls2Table";
const Luna<GameLua>::RegType GameLua::Register[] = {
	{ "writeInt", &GameLua::writeInt },
	{ "readInt", &GameLua::readInt },
	{ "writePtr", &GameLua::writePtr },
	{ "readPtr", &GameLua::readPtr },
	{ "writeShort", &GameLua::writeShort },
	{ "readShort", &GameLua::readShort },
	{ "writeByte", &GameLua::writeByte },
	{ "readByte", &GameLua::readByte },
	{ "pressKey", &GameLua::pressKey },
	{ "baseAddress", &GameLua::baseAddress, },
	{ "isNull", &GameLua::isNull, },
	{ "toPtr", &GameLua::toPtr },
	{ "fromPtr", &GameLua::fromPtr },
	{ "addPtr", &GameLua::addPtr },
	{ 0 }
};