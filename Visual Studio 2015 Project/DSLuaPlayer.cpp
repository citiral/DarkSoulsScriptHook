#include "stdafx.h"
#include "DSLuaPlayer.h"


DSLuaPlayer::DSLuaPlayer(DSPlayer* player) :
	_player(player)
{
}

DSLuaPlayer::DSLuaPlayer(lua_State* L) {
	D_OUT("Please do not manually construct Player instances. (It just won't work)");
}

DSLuaPlayer::~DSLuaPlayer()
{
}

int DSLuaPlayer::getHealth(lua_State* L)
{
	lua_pushnumber(L, _player->getHealth());
	return 1;
}

int DSLuaPlayer::setHealth(lua_State * L)
{
	int health = luaL_checkinteger(L, 2);
	_player->setHealth(health);
	return 0;
}


const char DSLuaPlayer::className[] = "Player";
const char DSLuaPlayer::tableName[] = "PlayerTable";
const Luna<DSLuaPlayer>::RegType DSLuaPlayer::Register[] = {
	{ "getHealth", &DSLuaPlayer::getHealth },
	{ "setHealth", &DSLuaPlayer::setHealth },
	{ 0 }
};