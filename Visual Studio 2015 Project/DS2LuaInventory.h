#pragma once

#include "DS2Inventory.h"
#include "luna.h"
extern "C" {
#include <lua.h>
}

class DS2LuaInventory
{
public:
	DS2LuaInventory(DS2Inventory* inv);
	DS2LuaInventory(lua_State* l);
	~DS2LuaInventory();

	//lua functions
	int getItemBasePointer(lua_State* l);
	int getHeadBasePointer(lua_State* l);
	int getWeaponBasePointer(lua_State* l);

	static const char className[];
	static const char tableName[];
	static const Luna<DS2LuaInventory>::RegType Register[];

private:
	DS2Inventory* _inv;
};

