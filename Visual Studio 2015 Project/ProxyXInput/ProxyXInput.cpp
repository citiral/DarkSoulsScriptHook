#define WIN32_LEAN_AND_MEAN		
#include <Windows.h>
#include "output.h"
#include "ProxyXInput.h"

// global variables
#pragma data_seg (".d3d9_shared")
HINSTANCE gl_hOriginalDll;
HINSTANCE gl_hThisInstance;
HANDLE _inputNamedpipe;
#pragma data_seg ()

BOOL WINAPI DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	// to avoid compiler lvl4 warnings 
	LPVOID lpDummy = lpReserved;
	lpDummy = NULL;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: InitInstance(hModule); break;
	case DLL_PROCESS_DETACH: ExitInstance(); break;

	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	}
	return TRUE;
}

/************************
 *PROXY DLL SHIT
 ************************/

typedef void(WINAPI *OrigXInputEnable)(BOOL);
typedef DWORD(WINAPI *OrigXInputGetAudioDeviceIds)(DWORD, LPWSTR, UINT*, LPWSTR, UINT*);
typedef DWORD(WINAPI *OrigXInputGetBatteryInformation)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
typedef DWORD(WINAPI *OrigXInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
typedef DWORD(WINAPI *OrigXInputGetDSoundAudioDeviceGuids)(DWORD, GUID*, GUID*);
typedef DWORD(WINAPI *OrigXInputGetKeystroke)(DWORD, DWORD, PXINPUT_KEYSTROKE);
typedef DWORD(WINAPI *OrigXInputGetState)(DWORD, XINPUT_STATE*);
typedef DWORD(WINAPI *OrigXInputSetState)(DWORD, XINPUT_VIBRATION*);

void LoadOriginalDll()
{
	char buffer[MAX_PATH];

	// Getting path to system dir and to d3d8.dll
	GetSystemDirectory(buffer, MAX_PATH);

	// Append dll name
	strcat_s(buffer, "\\xinput1_3.dll");

	// try to load the system's d3d9.dll, if pointer empty
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

	// Debug
	if (!gl_hOriginalDll)
	{
		::ExitProcess(0); // exit the hard way
	}

	_inputNamedpipe = CreateMailslot("\\\\.\\mailslot\\dslua", 1024, 0, NULL);
	//_inputNamedpipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\dslua"), PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1024 * 16, 1024 * 16, NMPWAIT_USE_DEFAULT_WAIT, NULL);
}

void InitInstance(HANDLE hModule)
{
	// Initialisation
	gl_hOriginalDll = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)hModule;

	LoadOriginalDll();
}

void ExitInstance()
{
	// Release the system's d3d9.dll
	if (gl_hOriginalDll)
	{
		FreeLibrary(gl_hOriginalDll);
		gl_hOriginalDll = NULL;
	}
	CloseHandle(_inputNamedpipe);
}

/************************
*PROXIED FUNCTIONS
************************/

void WINAPI XInputEnable(_In_ BOOL enable)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputEnable func = (OrigXInputEnable)GetProcAddress(gl_hOriginalDll, "XInputEnable");
	func(enable);
}

DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetBatteryInformation func = (OrigXInputGetBatteryInformation)GetProcAddress(gl_hOriginalDll, "XInputGetBatteryInformation");
	DWORD response = func(dwUserIndex, devType, pBatteryInformation);
	return response;
}

DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetCapabilities func = (OrigXInputGetCapabilities)GetProcAddress(gl_hOriginalDll, "XInputGetCapabilities");
	return func(dwUserIndex, dwFlags, pCapabilities);
}

DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetDSoundAudioDeviceGuids func = (OrigXInputGetDSoundAudioDeviceGuids)GetProcAddress(gl_hOriginalDll, "XInputGetDSoundAudioDeviceGuids");
	return func(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetKeystroke func = (OrigXInputGetKeystroke)GetProcAddress(gl_hOriginalDll, "XInputGetKeystroke");
	return func(dwUserIndex, dwReserved, pKeystroke);
}

DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetState func = (OrigXInputGetState)GetProcAddress(gl_hOriginalDll, "XInputGetState");
	DWORD result = func(dwUserIndex, pState);

		//DWORD waitingBytes;
		//PeekNamedPipe(_inputNamedpipe, NULL, 0, NULL, &waitingBytes, NULL);

		//handle only the bytes waiting right now (prevents unlimited looping)
		//while (waitingBytes >= 2) {
		//	waitingBytes -= 2;
		
	unsigned long read = 0;
	unsigned char data[2];

	ReadFile(_inputNamedpipe, data, 2, &read, NULL);

	if (read == 2) {
		WORD button = (((WORD)data[0]) << 8) + data[1];
		pState->Gamepad.wButtons |= button;
	}
	
	return result;
}

DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
{
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputSetState func = (OrigXInputSetState)GetProcAddress(gl_hOriginalDll, "XInputSetState");
	return func(dwUserIndex, pVibration);
}