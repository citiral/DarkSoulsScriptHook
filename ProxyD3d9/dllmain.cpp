// d3d9proxy.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "dllmain.h"
#include "hookIDirect3D9.h"
#include "debug.h"
#include "messagehook.h"

#pragma comment(linker, "/section:HOOKDAT,RWS") 
#pragma data_seg( "HOOKDAT" )
HINSTANCE hOriginalDx9 = NULL;
HMODULE hModule = NULL;
hookIDirect3D9* hookedIDirect3D9 = NULL;
#pragma data_seg()

BOOL APIENTRY DllMain(HMODULE mod,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hModule = mod;
		initializeProxy();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		exitProxy();
		break;
	}
	return TRUE;
}

IDirect3D9 * WINAPI Direct3DCreate9(UINT SDKVersion) {
	printString("Creating an IDirect3D9");

	typedef IDirect3D9* (WINAPI* func)(UINT SDKVersion);

	func originalFunc = (func)GetProcAddress(hOriginalDx9, "Direct3DCreate9");

	hookedIDirect3D9 = new hookIDirect3D9(originalFunc(SDKVersion));

	printString("register window message hooks");
	//messagehook::createHooks(hModule);

	return hookedIDirect3D9;
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions) {
	printString("Calling D3DPERF_SetOptions");

	typedef void (WINAPI* func)(DWORD dwOptions);

	func originalFunc = (func)GetProcAddress(hOriginalDx9, "D3DPERF_SetOptions");

	if (originalFunc == NULL) {
		printString("Failed to find original D3DPERF_SetOptions... this sucks..");
	}

	return originalFunc(dwOptions);
}

void initializeProxy() {
	printString("attaching dx9");

	char libfolder[1024];

	::GetSystemDirectoryA(libfolder, 1024);

	printString("System folder is:");

	printString(libfolder);

	strcat_s(libfolder, "\\d3d9.dll");

	printString("so, correct me if i'm wrong, but the dll should be at");
	printString(libfolder);

	if (hOriginalDx9 == NULL) {
		hOriginalDx9 = ::LoadLibraryA(libfolder);
	}
	if (hOriginalDx9 != NULL) {
		printString("attached!");
	}
	else {
		printString("Failed to attach DX9.. ABORT! ABORT!");
	}


}

void exitProxy() {
	if (hookedIDirect3D9 != NULL) {
		printString("Cleaning up hooks. Arrrrrrgh!");
		hookedIDirect3D9->cleanup();
	}

	if (hOriginalDx9 != NULL) {
		printString("Freeing DX9... And now, your watch has ended.");
		::FreeLibrary(hOriginalDx9);
		printString("You know nothing, DX9.");
		hOriginalDx9 = NULL;
	}
}