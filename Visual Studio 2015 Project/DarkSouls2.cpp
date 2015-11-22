#include "stdafx.h"
#include "DarkSouls2.h"
#include "luna.h"
#include "DarkSouls2Lua.h"
#include "DS2LuaPlayer.h"
#include "DS2LuaInventory.h"

DarkSouls2::DarkSouls2()
{
	if (fetchProcess(L"DarkSoulsII.exe")) {
		D_OUT("Process found and opened.");
		fetchBasePointer();
	}
	else {
		R_ERR("No process has been found or failed to open the handle.");
	}

	initWrappers();
}


DarkSouls2::~DarkSouls2()
{
}

void DarkSouls2::initWrappers()
{
	_player.init(this);
	_inventory.init(this);
}

void DarkSouls2::registerLua(lua_State* l)
{
	Luna<DS2LuaPlayer>::Register(l);
	Luna<DarkSouls2Lua>::Register(l);
	Luna<DS2LuaInventory>::Register(l);

	Luna<DS2LuaPlayer>::create(l, &_player);
	lua_setglobal(l, "player");

	Luna<DS2LuaInventory>::create(l, &_inventory);
	lua_setglobal(l, "inventory");

	Luna<DarkSouls2Lua>::create(l, this);
	lua_setglobal(l, "ds2");


	//Luna<DS2LuaPlayer>::create(l, &_player);
	//lua_setglobal(l, "tplayer");
	//LuaPlayer** luaplayer = (LuaPlayer**)lua_newuserdata(_l, sizeof(LuaPlayer*));

	//luaplayer = new LuaPlayer(_ds->getPlayer());
	//luaL_getmetatable(_l, "Player");
	//lua_setmetatable(_l, -2);

	//Luna<DS2LuaPlayer>::create(l, &_player);
	//lua_setglobal(l, "player");
}