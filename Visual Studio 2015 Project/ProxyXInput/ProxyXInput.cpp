#define WIN32_LEAN_AND_MEAN		
#include <Windows.h>
#include "output.h"
#include "ProxyXInput.h"

// global variables
#pragma data_seg (".d3d9_shared")
HINSTANCE           gl_hOriginalDll;
HINSTANCE			gl_hThisInstance;
#pragma data_seg ()

BOOL WINAPI DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	// to avoid compiler lvl4 warnings 
	LPVOID lpDummy = lpReserved;
	lpDummy = NULL;
	initOutput();
	output << "Starting dll!" << std::endl << std::flush;

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

typedef void *(WINAPI *OrigXInputEnable)(BOOL);
typedef DWORD(WINAPI *OrigXInputGetAudioDeviceIds)(DWORD, LPWSTR, UINT*, LPWSTR, UINT*);
typedef DWORD(WINAPI *OrigXInputGetBatteryInformation)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
typedef DWORD(WINAPI *OrigXInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
typedef DWORD(WINAPI *OrigXInputGetDSoundAudioDeviceGuids)(DWORD, GUID*, GUID*);
typedef DWORD(WINAPI *OrigXInputGetKeystroke)(DWORD, DWORD, PXINPUT_KEYSTROKE);
typedef DWORD(WINAPI *OrigXInputGetState)(DWORD, XINPUT_STATE*);
typedef DWORD(WINAPI *OrigXInputSetState)(DWORD, XINPUT_VIBRATION*);

void LoadOriginalDll(void)
{
	output << "PROXYDLL: aaaa\r\n" << std::endl << std::flush;
	char buffer[MAX_PATH];

	// Getting path to system dir and to d3d8.dll
	GetSystemDirectory(buffer, MAX_PATH);

	output << "PROXYDLL: about to load dll\r\n" << std::endl << std::flush;

	// Append dll name
	strcat_s(buffer, "\\xinput1_3.dll");
	output << "PROXYDLL: cat...\r\n" << std::endl << std::flush;

	// try to load the system's d3d9.dll, if pointer empty
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

	output << "PROXYDLL: loaded...\r\n" << std::endl << std::flush;

	// Debug
	if (!gl_hOriginalDll)
	{
		output << "PROXYDLL: Original xinput1_3.dll not loaded ERROR ****\r\n" << std::endl << std::flush;
		::ExitProcess(0); // exit the hard way
	}
	output << "PROXYDLL: Orignal DLL loaded ****\r\n" << std::endl << std::flush;
}

void InitInstance(HANDLE hModule)
{
	output << "PROXYDLL: InitInstance called." << std::endl << std::flush;

	// Initialisation
	gl_hOriginalDll = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)hModule;
	output << "PROXYDLL: InitInstance done." << std::endl << std::flush;
}

void ExitInstance()
{
	output << "PROXYDLL: ExitInstance called." << std::endl << std::flush;

	// Release the system's d3d9.dll
	if (gl_hOriginalDll)
	{
		FreeLibrary(gl_hOriginalDll);
		gl_hOriginalDll = NULL;
	}
}


/************************
*PROXIED FUNCTIONS
************************/

void WINAPI XInputEnable(
	_In_ BOOL enable
	)
{
	output << "PROXYDLL: Xinput enable called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputEnable func = (OrigXInputEnable)GetProcAddress(gl_hOriginalDll, "XInputEnable");
	func(enable);
}

DWORD WINAPI XInputGetAudioDeviceIds(
	DWORD  dwUserIndex,
	LPWSTR pRenderDeviceId,
	UINT   *pRenderCount,
	LPWSTR pCaptureDeviceId,
	UINT   *pCaptureCount)
{
	output << "PROXYDLL: XInputGetAudioDeviceIds called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	//OrigXInputGetAudioDeviceIds func = (OrigXInputGetAudioDeviceIds)GetProcAddress(gl_hOriginalDll, "XInputGetAudioDeviceIds");
	//return func(dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount);
	return -1;
}

DWORD WINAPI XInputGetBatteryInformation(
	 DWORD                      dwUserIndex,
	 BYTE                       devType,
	XINPUT_BATTERY_INFORMATION *pBatteryInformation
	)
{
	output << "PROXYDLL: XInputGetBatteryInformation called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetBatteryInformation func = (OrigXInputGetBatteryInformation)GetProcAddress(gl_hOriginalDll, "XInputGetBatteryInformation");
	return func(dwUserIndex, devType, pBatteryInformation);
}

DWORD WINAPI XInputGetCapabilities(
	 DWORD                dwUserIndex,   // Index of the gamer associated with the device
	 DWORD                dwFlags,       // Input flags that identify the device type
	XINPUT_CAPABILITIES* pCapabilities  // Receives the capabilities

	)
{
	output << "PROXYDLL: XInputGetCapabilities called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetCapabilities func = (OrigXInputGetCapabilities)GetProcAddress(gl_hOriginalDll, "XInputGetCapabilities");
	return func(dwUserIndex, dwFlags, pCapabilities);
}

DWORD WINAPI XInputGetDSoundAudioDeviceGuids(
	DWORD dwUserIndex,
	GUID* pDSoundRenderGuid,
	GUID* pDSoundCaptureGuid
	)
{
	output << "PROXYDLL: XInputGetDSoundAudioDeviceGuids called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetDSoundAudioDeviceGuids func = (OrigXInputGetDSoundAudioDeviceGuids)GetProcAddress(gl_hOriginalDll, "XInputGetDSoundAudioDeviceGuids");
	return func(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

DWORD WINAPI XInputGetKeystroke(
	DWORD             dwUserIndex,
	DWORD             dwReserved,
	PXINPUT_KEYSTROKE pKeystroke
	)
{
	output << "PROXYDLL: XInputGetKeystroke called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetKeystroke func = (OrigXInputGetKeystroke)GetProcAddress(gl_hOriginalDll, "XInputGetKeystroke");
	return func(dwUserIndex, dwReserved, pKeystroke);
}

DWORD WINAPI XInputGetState(
	 DWORD        dwUserIndex,
	XINPUT_STATE *pState

	)
{
	output << "PROXYDLL: XInputGetState called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputGetState func = (OrigXInputGetState)GetProcAddress(gl_hOriginalDll, "XInputGetState");
	return func(dwUserIndex, pState);
}

DWORD WINAPI XInputSetState(
	 DWORD            dwUserIndex,
	 XINPUT_VIBRATION *pVibration
	)
{
	output << "PROXYDLL: XInputSetState called." << std::endl << std::flush;
	if (!gl_hOriginalDll) LoadOriginalDll();
	OrigXInputSetState func = (OrigXInputSetState)GetProcAddress(gl_hOriginalDll, "XInputSetState");
	return func(dwUserIndex, pVibration);
}