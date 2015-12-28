#include "stdafx.h"
#include "Game.h"
#include <TlHelp32.h>
#include <stdlib.h>
#include <stdio.h>
#include <Psapi.h>
#include <windows.h>

Game::Game()
{
	_inputNamedpipe = CreateFile(TEXT("\\\\.\\mailslot\\dslua"), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}


Game::~Game()
{
	CloseHandle(_inputNamedpipe);
}

void* Game::getBaseAddress()
{
	return _basePointer;
}

void Game::pressKey(unsigned short key)
{
	unsigned char data[2];
	data[0] = key >> 8;
	data[1] = key;
	DWORD written;
	//send the key press
	WriteFile(_inputNamedpipe, data, 2, &written, NULL);
	//and then release it
	data[0] = 0;
	data[1] = 0;
	WriteFile(_inputNamedpipe, data, 2, &written, NULL);
	D_OUT("written " << written << " bytes.");
}

bool Game::fetchProcess(const wchar_t* processname, const wchar_t* windowname)
{
	//first, fetch the window
	_window = FindWindowW(NULL, windowname);
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
	wchar_t xinput[255];
	GetModuleFileNameEx(_process, NULL, filename, sizeof(wchar_t) * 255);
	
	//get the xinput filename
	//wcscpy_s(xinput, filename);
	//wchar_t* lastindex = wcsrchr(xinput, '\\');
	//wcsncpy_s(lastindex+1,  sizeof(char) * 14, L"XINPUT1_3.dll", sizeof(char) * 14);
	
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
		}/* else if (wcscmp(xinput, modulename) == 0) {
			_xinputPointer = handles[i];
			D_OUT("got xinput! " << _xinputPointer);
			
			D_OUT("callback is " << GetProcAddress(LoadLibrary(xinput), "XInputGetState"));
		}*/
	}
}
