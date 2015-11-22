#include "stdafx.h"
#include "DSPlayer.h"
#include "DarkSouls.h"


DSPlayer::DSPlayer():
	_ds(nullptr)
{
}


DSPlayer::~DSPlayer()
{
}

void DSPlayer::init(DarkSouls* ds)
{
	_ds = ds;
	getPlayerPointer();
}

int DSPlayer::getHealth()
{
	int h = 0;
	_ds->readMemory<int>((char*)_playerPointer + 0x2d4, &h);
	return h;
}

void DSPlayer::setHealth(int health)
{
	_ds->writeMemory<int>((char*)_playerPointer + 0x2d4, &health);
}

void DSPlayer::getPlayerPointer()
{
	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x00EDF9E8, &_playerPointer);
	_ds->readMemory<void*>(_playerPointer, &_playerPointer);
	D_OUT("Player pointer is " << _playerPointer << ".");
}
