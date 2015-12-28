#include "LuaMod.h"
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include "inputlua.h"
#include "pointerlua.h"
#include "drawinglua.h"
#include "liblua.h"
#include "functioncallinglua.h"
#include "debug.h"

LuaMod::LuaMod(std::string scriptname):
	_scriptname(scriptname), _running(false)
{
}


LuaMod::~LuaMod()
{
	if (_running)
		stop();
}

void LuaMod::start()
{
	_running = true;
	_l = luaL_newstate();
	luaL_openlibs(_l);
	
	addBindings();

	if (luaL_loadfile(_l, _scriptname.c_str()) || lua_pcall(_l, 0, 0, 0)) {
		printString(lua_tostring(_l, -1));
	}
}

void LuaMod::stop()
{
	_running = false;
	lua_close(_l);
}

void LuaMod::update(float dt)
{
	lua_getglobal(_l, "update");
	lua_pushnumber(_l, dt);
	if (lua_pcall(_l, 1, 0, 0)) {
		printString(lua_tostring(_l, -1));
	}
}

void LuaMod::addBindings()
{
	//make an input table
	registerInput(_l);
	registerPointer(_l);
	registerDrawing(_l);
	registerLib(_l);
	registerFunctionCalling(_l);
}
