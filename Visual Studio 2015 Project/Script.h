#pragma once

#include "DarkSouls.h"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Script
{
public:
	Script(Game* ds, const char* filename);
	~Script();

private:

	const char* _filename;
	lua_State* _l;
};

