#include <Windows.h>
#include <vector>
#include "debug.h"
#define KEY_DOWN_MASK 0x80000000

namespace input {

	std::vector<short> previous(256);
	std::vector<short> current(256);

	void initialize()
	{
	}

	void cleanup()
	{
	}

	void update()
	{
		previous.swap(current);
		for (int i = 0; i < 256; i++) {
			current[i] = GetKeyState(i);
		}
	}

	bool getKeyPressed(unsigned char key)
	{
		return ((current[key] & 0x80000000) == 0x80000000) && (previous[key] & 0x80000000) == 0;//(_keyboardState[key] & KEY_DOWN_MASK) != 0;
	}

	short getKeyState(unsigned char key)
	{
		return current[key];
	}
}