#include "stdafx.h"
#include "DS2LuaInventory.h"


DS2LuaInventory::DS2LuaInventory(DS2Inventory* inv):
	_inv(inv)
{
}

DS2LuaInventory::DS2LuaInventory(lua_State* l)
{
	D_OUT("Please do not manually construct Inventory instances. (It just won't work)");
}

DS2LuaInventory::~DS2LuaInventory()
{
}

int DS2LuaInventory::getItemBasePointer(lua_State * l)
{
	int index = luaL_checknumber(l, 2);
	void* data = _inv->getItemBasePointer(index);

	lua_pushlightuserdata(l, data);
	return 1;
}

int DS2LuaInventory::getItem(lua_State* l/*, index*/)
{
	int index = luaL_checknumber(l, 2);
	int data = _inv->getItem(index);

	lua_pushnumber(l, data);
	return 1;
}

int DS2LuaInventory::setItem(lua_State* l/*, index, id*/)
{
	int index = luaL_checknumber(l, 2);
	int id = luaL_checknumber(l, 3);

	_inv->setItem(index, id);
	
	return 0;
}

int DS2LuaInventory::getBasePointer(lua_State * l)
{
	lua_pushlightuserdata(l, _inv->getBasePointer());
	return 1;
}

const char DS2LuaInventory::className[] = "Inventory";
const char DS2LuaInventory::tableName[] = "InventoryTable";
const Luna<DS2LuaInventory>::RegType DS2LuaInventory::Register[] = {
	/*{ "getItem", &DS2LuaInventory::getItem },*/
	/*{ "setItem", &DS2LuaInventory::setItem },*/
	{ "getItemBasePointer", &DS2LuaInventory::getItemBasePointer },
	{ "getBasePointer", &DS2LuaInventory::getBasePointer },
	{ 0 }
};