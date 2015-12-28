#include "MessageHook.h"
#include "debug.h"

/*#pragma comment(linker, "/section:MESSAGEHOOKDAT,RWS") 
#pragma data_seg( "MESSAGEHOOKDAT" )
MouseData mouseData = { 0,0,false,false,false };
bool keyStates[256];
#pragma data_seg()*/
bool keyIsPressed(int k) {
	return (GetAsyncKeyState(k) & 0x80000000) != 0;
	//if (k >= 0 && k < 256)
	//	return keyStates[k];
	//return 0;
}
/*
void createHooks(HMODULE hModule) {
	if (SetWindowsHookEx(WH_MOUSE, &MouseHookProc, hModule, GetCurrentThreadId()) == NULL) {
		printString("error setting mouse hook");
	}

	if (SetWindowsHookEx(WH_KEYBOARD, &KeyHookProc, hModule, GetCurrentThreadId()) == NULL) {
		printString("error setting kb hook");
	}
}

MouseData& getMouseData() {
	return mouseData;
}

LRESULT CALLBACK CallHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	char string[255];
	_itoa_s(nCode, string, 2);
	printString("key hook proc: ");
	printString(string);

	//if (nCode < 0) return CallNextHookEx(NULL, nCode, wParam, lParam);

	int key = wParam;//((PKBDLLHOOKSTRUCT)lParam)->vkCode;
	
	if ((nCode & WM_KEYUP) == WM_KEYUP)
		keyStates[key] = false;
	else if ((nCode & WM_KEYDOWN) == WM_KEYDOWN)
		keyStates[key] = true;

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
*/