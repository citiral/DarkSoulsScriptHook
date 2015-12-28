#pragma once

#include "pch.h"

extern HINSTANCE hOriginalDx9;
extern hookIDirect3D9* hookedIDirect3D9;
extern HMODULE hModule;

void initializeProxy();
void exitProxy();
void setCooperative();

IDirect3D9 * WINAPI Direct3DCreate9(UINT SDKVersion);
void WINAPI D3DPERF_SetOptions(DWORD dwOptions);