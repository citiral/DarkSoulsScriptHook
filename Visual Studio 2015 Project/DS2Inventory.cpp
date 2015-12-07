#include "stdafx.h"
#include "DS2Inventory.h"
#include "DarkSouls2.h"

DS2Inventory::DS2Inventory()
{
}


DS2Inventory::~DS2Inventory()
{
}

void DS2Inventory::init(DarkSouls2* ds)
{
	_ds = ds;
	fetchBasePointer();
}

void* DS2Inventory::getItemBasePointer()
{
	void* data;
	_ds->readMemory<void*>((char*)_inventory + 0x10, &data);
	return data;
}

void* DS2Inventory::getHeadBasePointer()
{
	return _headStart;
}

void* DS2Inventory::getWeaponBasePointer()
{
	return _weaponStart;
}

/////0x18 is gestures
void DS2Inventory::fetchBasePointer()
{
	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x160ABC0, &_inventory);
	_ds->readMemory<void*>((char*)_inventory + 0x4F8, &_inventory);
	_ds->readMemory<void*>((char*)_inventory + 0x258, &_inventory);
	//_ds->readMemory<void*>((char*)_inventory + 0x10, &_inventory);

	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x186D4A8, &_chestStart);
	_ds->readMemory<void*>((char*)_chestStart + 0x8, &_chestStart);
	_ds->readMemory<void*>((char*)_chestStart + 0x130, &_chestStart);
	_ds->readMemory<void*>((char*)_chestStart + 0x128, &_chestStart);
	_chestStart = (char*)_chestStart + 0x50;

	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x160ABC0, &_headStart);
	_ds->readMemory<void*>((char*)_headStart + 0x40, &_headStart);
	_ds->readMemory<void*>((char*)_headStart + 0x160, &_headStart);
	_ds->readMemory<void*>((char*)_headStart + 0x10, &_headStart);
	_headStart = (char*)_headStart + 0xA0;

	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x186D4A8, &_weaponStart);
	_ds->readMemory<void*>((char*)_weaponStart + 0x8, &_weaponStart);
	_ds->readMemory<void*>((char*)_weaponStart + 0x130, &_weaponStart);
	_ds->readMemory<void*>((char*)_weaponStart + 0x120, &_weaponStart);
	_weaponStart = (char*)_weaponStart + 0x50;

	D_OUT("start is " << _weaponStart);
}
