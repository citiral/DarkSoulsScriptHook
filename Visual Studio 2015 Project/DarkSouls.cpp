#include "stdafx.h"
#include "DarkSouls.h"
#include "luna.h"
#include "DSLuaPlayer.h"

DarkSouls::DarkSouls()
{
	if (fetchProcess(L"DARKSOULS.exe")) {
		D_OUT("Process found and opened.");
		fetchBasePointer();
	} else {
		R_ERR("No process has been found or failed to open the handle.");
	}

	initWrappers();
}


DarkSouls::~DarkSouls()
{
}

void DarkSouls::initWrappers()
{
	_player.init(this);
}

DSPlayer* DarkSouls::getPlayer()
{
	return &_player;
}

void DarkSouls::registerLua(lua_State* l)
{
	Luna<DSLuaPlayer>::create(l, getPlayer());
	lua_setglobal(l, "player");
}