#include "stdafx.h"
#include "Script.h"
#include "luna.h"
#include "DSLuaPlayer.h"

Script::Script(Game* ds, const char* filename):
	_filename(filename)
{
	_l = luaL_newstate();
	luaL_openlibs(_l);
	
	ds->registerLua(_l);
	
	if (luaL_loadfile(_l, filename) || lua_pcall(_l, 0, 0, 0)) {
		printf("%s\n", lua_tostring(_l, -1));
	}
}


Script::~Script()
{
	lua_close(_l);
}
/*
void Script::registerClasses()
{
	Luna<DSLuaPlayer>::Register(_l);
}*/
/*
void Script::registerGlobals()
{
	Luna<DSLuaPlayer>::create(_l, _ds->getPlayer());
	lua_setglobal(_l, "player");*/
	//LuaPlayer** luaplayer = (LuaPlayer**)lua_newuserdata(_l, sizeof(LuaPlayer*));
	
	/**luaplayer = new LuaPlayer(_ds->getPlayer());
	luaL_getmetatable(_l, "Player");
	lua_setmetatable(_l, -2);
	*/
/*
}*/