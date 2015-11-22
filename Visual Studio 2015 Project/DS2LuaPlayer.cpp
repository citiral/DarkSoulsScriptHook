#include "stdafx.h"
#include "DS2LuaPlayer.h"


DS2LuaPlayer::DS2LuaPlayer(DS2Player* player) :
	_player(player)
{
}

DS2LuaPlayer::DS2LuaPlayer(lua_State* l)
{
	D_OUT("Do not manually construct Player instances. (It just won't work)");
}


DS2LuaPlayer::~DS2LuaPlayer()
{
}

int DS2LuaPlayer::getBasePointer(lua_State* L)
{
	lua_pushlightuserdata(L, _player->getBasePointer());
	return 1;
}

int DS2LuaPlayer::getBasePointer2(lua_State* L)
{
	lua_pushlightuserdata(L, _player->getBasePointer2());
	return 1;
}


const char DS2LuaPlayer::className[] = "Player";
const char DS2LuaPlayer::tableName[] = "PlayerTable";
const Luna<DS2LuaPlayer>::RegType DS2LuaPlayer::Register[] = {
	{ "getBasePointer", &DS2LuaPlayer::getBasePointer },
	{ "getBasePointer2", &DS2LuaPlayer::getBasePointer2 },
	//{ "getHealth", &DS2LuaPlayer::getHealth },
	//{ "setHealth", &DS2LuaPlayer::setHealth },
	{ 0 }
};