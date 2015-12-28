#include "drawinglua.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "Drawing.h"

void drawText(const char* text, int x, int y, D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255));

int lua_drawText(lua_State* l)
{
	if (lua_gettop(l) == 3) {
		const char* text = luaL_checkstring(l, 1);
		int x = luaL_checknumber(l, 2);
		int y = luaL_checknumber(l, 3);

		drawing::drawText(text, x, y);
	}
	else {
		const char* text = luaL_checkstring(l, 1);
		int x = luaL_checknumber(l, 2);
		int y = luaL_checknumber(l, 3);
		LPD3DXFONT font = (LPD3DXFONT)lua_touserdata(l, 4);

		drawing::drawText(text, x, y, font);
	}

	return 0;
}

int lua_createFont(lua_State* l)
{
	if (lua_gettop(l) == 2) {
		int size = luaL_checknumber(l, 1);
		const char* fontface = luaL_checkstring(l, 2);
		lua_pushlightuserdata(l, drawing::createFont(size, fontface));
	}
	else {
		int size = luaL_checknumber(l, 1);
		lua_pushlightuserdata(l, drawing::createFont(size));
	}
	return 1;
}

int lua_destroyFont(lua_State* l)
{
	LPD3DXFONT font = (LPD3DXFONT)lua_touserdata(l, 1);

	drawing::destroyFont(font);

	return 0;
}

luaL_Reg drawFuncs[] = {
	{ "drawText", lua_drawText },
	{ "createFont", lua_createFont },
	{ "destroyFont", lua_destroyFont },
	0
};

void registerDrawing(lua_State* l)
{
	//make an input table
	lua_newtable(l);
	luaL_setfuncs(l, drawFuncs, 0);
	lua_setglobal(l, "drawing");
}