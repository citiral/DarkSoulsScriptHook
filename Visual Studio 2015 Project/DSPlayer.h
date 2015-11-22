#pragma once

class DarkSouls;

class DSPlayer
{
public:
	DSPlayer();
	~DSPlayer();

	void init(DarkSouls* ds);

	int getHealth();
	void setHealth(int health);

private:
	void getPlayerPointer();

	void* _playerPointer;
	DarkSouls* _ds;
};

