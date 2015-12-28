#pragma once

namespace input {
	void initialize();
	void cleanup();

	void update();

	bool getKeyPressed(unsigned char key);
	short getKeyState(unsigned char key);
}