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

int DSLuaPlayer::getBasePointer(lua_State * L)
{
	lua_pushlightuserdata(L, _player->getBasePointer());
	return 1;
}

int DSLuaPlayer::getBasePointer2(lua_State * L)
{
	lua_pushlightuserdata(L, _player->getBasePointer2());
	return 1;
}


const char DSLuaPlayer::className[] = "Player";
const char DSLuaPlayer::tableName[] = "PlayerTable";
const Luna<DSLuaPlayer>::RegType DSLuaPlayer::Register[] = {
	{ "getBasePointer", &DSLuaPlayer::getBasePointer },
	{ "getBasePointer2", &DSLuaPlayer::getBasePointer2 },
	{ 0 }
};