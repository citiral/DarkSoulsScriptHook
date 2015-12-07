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
	lua_pushlightuserdata(l, _inv->getItemBasePointer());
	return 1;
}

int DS2LuaInventory::getHeadBasePointer(lua_State * l)
{
	lua_pushlightuserdata(l, _inv->getHeadBasePointer());
	return 1;
}

int DS2LuaInventory::getWeaponBasePointer(lua_State * l)
{
	lua_pushlightuserdata(l, _inv->getWeaponBasePointer());
	return 1;
}


const char DS2LuaInventory::className[] = "Inventory";
const char DS2LuaInventory::tableName[] = "InventoryTable";
const Luna<DS2LuaInventory>::RegType DS2LuaInventory::Register[] = {
	{ "getItemBasePointer", &DS2LuaInventory::getItemBasePointer },
	{ "getHeadBasePointer", &DS2LuaInventory::getHeadBasePointer },
	{ "getWeaponBasePointer", &DS2LuaInventory::getWeaponBasePointer },
	{ 0 }
}; 