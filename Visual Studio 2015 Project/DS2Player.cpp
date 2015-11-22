#include "stdafx.h"
#include "DS2Player.h"
#include "DarkSouls2.h"

DS2Player::DS2Player()
{
}


DS2Player::~DS2Player()
{
}

void DS2Player::init(DarkSouls2* ds)
{
	_ds = ds;
	getPlayerPointer();
}

void DS2Player::setHealth(int health)
{
	_ds->writeMemory<int>((char*)_playerPointer + 0x168, &health);
}

int DS2Player::getHealth()
{
	int health;
	_ds->readMemory<int>((char*)_playerPointer + 0x168, &health);
	return health;
}

void* DS2Player::getBasePointer()
{
	return _playerPointer;
}

void * DS2Player::getBasePointer2()
{
	void* ptr;
	_ds->readMemory<void*>((char*)_playerPointer + 0x490, &ptr);
	return ptr;
}

void DS2Player::getPlayerPointer()
{
	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x16829A0, &_playerPointer);
	_ds->readMemory<void*>((char*)_playerPointer+0x20, &_playerPointer);
	D_OUT("Player pointer is " << _playerPointer << ".");
}