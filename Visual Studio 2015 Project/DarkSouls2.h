#pragma once

#include "Game.h"
#include "DS2Player.h"
#include "DS2Inventory.h"

class DarkSouls2 : public Game
{
public:
	DarkSouls2();
	~DarkSouls2();

	void DarkSouls2::registerLua(lua_State* l);

private:
	void initWrappers();
	DS2Player _player;
	DS2Inventory _inventory;
};

