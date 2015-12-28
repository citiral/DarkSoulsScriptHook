#pragma once

class DarkSouls;

class DSPlayer
{
public:
	DSPlayer();
	~DSPlayer();

	void init(DarkSouls* ds);

	void* getBasePointer();
	void* getBasePointer2();

private:
	void calculateBasePointer();

	void* _playerPointer;
	void* _playerPointer2;
	DarkSouls* _ds;
};

