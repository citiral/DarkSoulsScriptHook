extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "functioncallinglua.h"
#include "FunctionCalling.h"

int lua_call_void_ptr_i32(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	void* arg1 = lua_touserdata(l, 2);
	int arg2 = luaL_checkinteger(l, 3);

	FunctionCalling::call_void(func, arg1, arg2);

	return 0;
}

int lua_call_void_i32(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	int arg1 = luaL_checkinteger(l, 2);

	FunctionCalling::call_void(func, arg1);

	return 0;
}

int lua_thiscall_void_i32(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	void* thispointer = lua_touserdata(l, 2);
	int arg1 = luaL_checkinteger(l, 3);

	FunctionCalling::thiscall_void(func, thispointer, arg1);

	return 0;
}

int lua_call_ptr_eax_edx_esi(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	int eax = lua_tonumber(l, 2);
	int edx = lua_tonumber(l, 3);
	int esi = lua_tonumber(l, 4);

	void* ret = FunctionCalling::call_ptr_eax_edx_esi(func, eax, edx, esi);
	lua_pushlightuserdata(l, ret);

	return 1;
}

int lua_call_ptr_eax_ecx_edx_esi(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	int eax = lua_tonumber(l, 2);
	int ecx = lua_tonumber(l, 3);
	int edx = lua_tonumber(l, 4);
	int esi = lua_tonumber(l, 5);

	void* ret = FunctionCalling::call_ptr_eax_ecx_edx_esi(func, eax, ecx, edx, esi);
	lua_pushlightuserdata(l, ret);

	return 1;
}

int lua_call_void_edx_1arg_pop_1(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	int edx = lua_tonumber(l, 2);
	void* arg1 = lua_touserdata(l, 3);

	FunctionCalling::call_void_edx_1arg_pop_1(func, edx, arg1);

	return 0;
}

int lua_call_void_eax_edx_1arg_pop_1(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	int eax = lua_tonumber(l, 2);
	int edx = lua_tonumber(l, 3);
	void* arg1 = lua_touserdata(l, 4);

	FunctionCalling::call_void_eax_edx_1arg_pop_1(func, eax, edx, arg1);

	return 0;
}

int lua_call_void_ecx_edx_edi(lua_State* l)
{
	void(*func)() = (void(*)())lua_touserdata(l, 1);
	int ecx = lua_tonumber(l, 2);
	int edx = lua_tonumber(l, 3);
	int edi = lua_tonumber(l, 4);

	FunctionCalling::call_void_ecx_edx_edi(func, ecx, edx, edi);

	return 0;
}

luaL_Reg functioncallingFuncs[] = {
	{ "call_void_i32_ptr", lua_call_void_ptr_i32 },
	{ "call_void_i32", lua_call_void_i32 },
	{ "thiscall_void_i32", lua_thiscall_void_i32 },
	{ "call_ptr_eax_edx_esi", lua_call_ptr_eax_edx_esi },
	{ "call_ptr_eax_ecx_edx_esi", lua_call_ptr_eax_ecx_edx_esi },
	{ "call_void_edx_1arg_pop_1", lua_call_void_edx_1arg_pop_1 },
	{ "call_void_eax_edx_1arg_pop_1", lua_call_void_eax_edx_1arg_pop_1 },
	{ "call_void_ecx_edx_edi", lua_call_void_ecx_edx_edi },
	0
};

void registerFunctionCalling(lua_State* l)
{
	//make an input table
	lua_newtable(l);
	luaL_setfuncs(l, functioncallingFuncs, 0);
	lua_setglobal(l, "func");
}