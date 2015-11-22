#pragma once

class DarkSouls2;

class DS2Player
{
public:
	DS2Player();
	~DS2Player();

	void init(DarkSouls2* ds);

	/*player functions*/
	void setHealth(int health);
	int getHealth();

	void* getBasePointer();
	void* getBasePointer2();

private:
	void getPlayerPointer();

	void* _playerPointer;
	DarkSouls2* _ds;
};

