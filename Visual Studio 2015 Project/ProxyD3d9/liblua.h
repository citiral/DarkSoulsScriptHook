#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <Windows.h>
}

int lua_ptrToString(lua_State* l);
int lua_printString(lua_State* l);
int lua_flushDebugFile(lua_State* l);

void registerLib(lua_State* l);