// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the D3D9PROXY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// D3D9PROXY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#include "hookIDirect3D9.h"

extern HINSTANCE hOriginalDx9;
extern hookIDirect3D9* hookedIDirect3D9;
extern HMODULE hModule;

void initializeProxy();
void exitProxy();
void setCooperative();

IDirect3D9 * WINAPI Direct3DCreate9(UINT SDKVersion);
void WINAPI D3DPERF_SetOptions( DWORD dwOptions );