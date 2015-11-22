#include "stdafx.h"
#include "Game.h"
#include <TlHelp32.h>
#include <stdlib.h>
#include <stdio.h>
#include <Psapi.h>
#include <windows.h>

Game::Game()
{
}


Game::~Game()
{
}

void* Game::getBaseAddress()
{
	return _basePointer;
}

void Game::sendKeyDown(int key)
{
	/*D_OUT("Window is " << _window);

	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	input.ki.wScan = key;
	input.ki.dwFlags = 0;
	input.ki.time = 0;

	SendInput(1, &input, sizeof(INPUT));*/
	AttachThreadInput(GetCurrentThreadId(), _thread, true);
	//SendMessageW(_window, WM_KEYDOWN, key, 0b0000000000000001000000000000000);
}

bool Game::fetchProcess(const wchar_t* processname)
{
	//first, fetch the window
	_window = FindWindowW(NULL, L"DARK SOULS II");
	D_OUT("Window is " << _window);
	_thread = GetWindowThreadProcessId(_window, NULL);
	D_OUT("Thread is " << _thread);
	//get a snapshot of the current process list
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//get the first process
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	bool processfound = Process32First(snapShot, &entry);

	//keep looping over all processes
	while (processfound) {
		char filename[MAX_PATH];
		int converted;

		//found a process
		if (wcscmp(entry.szExeFile, processname) == 0) {
			//open it
			_process = OpenProcess(PROCESS_ALL_ACCESS, false, entry.th32ProcessID);
			return  _process != NULL;
		}

		//continue to the next process
		processfound = Process32Next(snapShot, &entry);
	}

	return false;
}

void Game::fetchBasePointer()
{
	//first get the name of the process
	wchar_t filename[255];
	GetModuleFileNameEx(_process, NULL, filename, sizeof(wchar_t) * 255);
	//then get a list of all handles
	HMODULE handles[128];
	unsigned long filledbuffer;
	if (EnumProcessModules(_process, handles, sizeof(HMODULE) * 128, &filledbuffer) == 0) {
		R_ERR("Error enuming modules: " << GetLastError());
	}
	int count = filledbuffer / sizeof(HMODULE);

	//look for the module with the correct name
	for (int i = 0; i < count; i++) {
		wchar_t modulename[255];
		GetModuleFileNameEx(_process, handles[i], modulename, sizeof(wchar_t) * 255);
		if (wcscmp(filename, modulename) == 0) {
			_basePointer = handles[i];
			break;
		}
	}
}
