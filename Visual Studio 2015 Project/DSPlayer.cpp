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
	calculateBasePointer();
}

void* DSPlayer::getBasePointer()
{
	return _playerPointer;
}

void* DSPlayer::getBasePointer2()
{
	return _playerPointer2;
}

void DSPlayer::calculateBasePointer()
{
	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x00F7A644, &_playerPointer);
	_ds->readMemory<void*>((char*)_playerPointer + 0x3C, &_playerPointer);

	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x00F75700, &_playerPointer2);
	_ds->readMemory<void*>((char*)_playerPointer2 + 0x8, &_playerPointer2);

	D_OUT("Player pointer is " << _playerPointer << ".");
}
