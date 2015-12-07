#pragma once

class DarkSouls2;

class DS2Inventory
{
public:
	DS2Inventory();
	~DS2Inventory();

	void init(DarkSouls2* ds);

	void* getItemBasePointer();
	void* getHeadBasePointer();
	void* getWeaponBasePointer();
	
private:
	void fetchBasePointer();

	void* _inventory;
	void* _chestStart;
	void* _headStart;
	void* _weaponStart;
	DarkSouls2* _ds;
};

