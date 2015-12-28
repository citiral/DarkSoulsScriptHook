#pragma once

#include <Windows.h>

/*struct MouseData {
	float x;
	float y;
	bool LMB;
	bool RMB;
	bool MMB;
};*/

//extern bool keyStates[256];

//extern MouseData mouseData;

bool keyIsPressed(int k);
/*void createHooks(HMODULE hModule);
MouseData& getMouseData();

LRESULT CALLBACK CallHookProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam);*/
