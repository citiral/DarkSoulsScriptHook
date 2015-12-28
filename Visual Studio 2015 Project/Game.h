#pragma once

#include <Windows.h>
#include <WinUser.h>
extern "C" {
#include "lua.h"
}

class Game
{
public:
	Game();
	virtual ~Game();

	/*
	raw memory access functions. Handle with care
	*/
	template <class T>
	void readMemory(void* address, T* target);
	template <class T>
	void writeMemory(void* address, T* data);
	void* getBaseAddress();

	/*
	sends a key press according to the key defintions for an XINPUT_STATE
	*/
	void pressKey(unsigned short key);

	/*Registers the class with lua*/
	virtual void registerLua(lua_State* l) = 0;

protected:
	/*
	Memory related functions and variables
	*/
	bool fetchProcess(const wchar_t* processname, const wchar_t* windowname);
	void fetchBasePointer();
	HANDLE _process;
	DWORD _thread;
	HWND _window;
	HANDLE _inputNamedpipe;
	void* _basePointer;
	//void* _xinputPointer;
};

template <class T>
void Game::readMemory(void* address, T* target)
{
	if (ReadProcessMemory(_process, address, target, sizeof(T), NULL) == 0) {
		R_ERR("Error reading [" << address << "]: " << GetLastError());
	}
}

template <class T>
void Game::writeMemory(void* address, T* data)
{
	if (WriteProcessMemory(_process, address, data, sizeof(T), NULL) == 0) {
		R_ERR("Error writing [" << address << "]: " << GetLastError());
	}
}