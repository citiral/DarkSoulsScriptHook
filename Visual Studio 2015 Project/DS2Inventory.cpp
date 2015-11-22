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

int DS2Inventory::getItem(int index)
{
	int item;
	_ds->readMemory((char*)getItemBasePointer(index) + 0x14, &item);
	return item;
}

void DS2Inventory::setItem(int index, int item)
{
	_ds->writeMemory((char*)getItemBasePointer(index) + 0x14, &item);
}
void * DS2Inventory::getItemBasePointer(int index)
{
	return (char*)_inventory + (index + 1) * 0x28;
}
void* DS2Inventory::getBasePointer()
{
	return _inventory;
}

void DS2Inventory::fetchBasePointer()
{
	_ds->readMemory<void*>((char*)_ds->getBaseAddress() + 0x160ABC0, &_inventory);
	_ds->readMemory<void*>((char*)_inventory + 0x4F8, &_inventory);
	_ds->readMemory<void*>((char*)_inventory + 0x258, &_inventory);
	_ds->readMemory<void*>((char*)_inventory + 0x10, &_inventory);
	D_OUT("Inventory base pointer is " << _inventory << ".");
}
