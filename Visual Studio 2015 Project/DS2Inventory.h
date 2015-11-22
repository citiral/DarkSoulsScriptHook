#pragma once

class DarkSouls2;

class DS2Inventory
{
public:
	DS2Inventory();
	~DS2Inventory();

	void init(DarkSouls2* ds);

	int getItem(int index);
	void setItem(int index, int item);
	void* getItemBasePointer(int index);
	void* getBasePointer();
	
private:
	void fetchBasePointer();

	void* _inventory;
	DarkSouls2* _ds;
};

