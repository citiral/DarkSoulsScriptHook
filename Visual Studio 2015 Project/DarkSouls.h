#pragma once

#include <Windows.h>
#include "DSPlayer.h"
#include "Game.h"

class DarkSouls : public Game
{
public:
	DarkSouls();
	~DarkSouls();

	/*
	Wrapping functions
	*/
	DSPlayer* getPlayer();

	void DarkSouls::registerLua(lua_State* l);
	
private:
	void initWrappers();
	DSPlayer _player;
};