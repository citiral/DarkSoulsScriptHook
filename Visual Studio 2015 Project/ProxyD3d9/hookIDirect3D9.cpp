#include "hookIDirect3D9.h"
#include "hookIDirect3DDevice9.h"
#include "d3d9proxy.h"
#include "debug.h"

HWND hookIDirect3D9::hWnd = NULL;

hookIDirect3D9::hookIDirect3D9(IDirect3D9* hookee)
{
	_hookee = hookee;
}


hookIDirect3D9::~hookIDirect3D9(void)
{
	printString("Destroying hookIDirect3D9");
	delete _hookee;
}

void hookIDirect3D9::cleanup() {
	printString("cleaning up hookIDirect3D9");
	_hookDevice->cleanup();
	
}

HRESULT hookIDirect3D9::CreateDevice(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) {
	printString("Creating a dx9 device.");

	hWnd = hFocusWindow;

	HRESULT result = _hookee->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	
	_hookDevice = new hookIDirect3DDevice9(*ppReturnedDeviceInterface);

	(*ppReturnedDeviceInterface) = _hookDevice;

	return result;
}
    
 /*** IUnknown methods ***/
HRESULT hookIDirect3D9::QueryInterface(REFIID riid, void** ppvObj) {
	return _hookee->QueryInterface(riid, ppvObj);
}

ULONG hookIDirect3D9::AddRef() {
	return _hookee->AddRef();
}

ULONG hookIDirect3D9::Release() {
	return _hookee->Release();
}

/*** IDirect3D9 methods ***/
HRESULT hookIDirect3D9::RegisterSoftwareDevice(THIS_ void* pInitializeFunction) {
	return _hookee->RegisterSoftwareDevice(pInitializeFunction);
}

UINT hookIDirect3D9::GetAdapterCount() {
	return _hookee->GetAdapterCount();
}

HRESULT hookIDirect3D9::GetAdapterIdentifier(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) {
	return _hookee->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT hookIDirect3D9::GetAdapterModeCount(THIS_ UINT Adapter,D3DFORMAT Format) {
	return _hookee->GetAdapterModeCount(Adapter, Format);
}

HRESULT hookIDirect3D9::EnumAdapterModes(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) {
	return _hookee->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT hookIDirect3D9::GetAdapterDisplayMode(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) {
	return _hookee->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT hookIDirect3D9::CheckDeviceType(THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) {
	return _hookee->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT hookIDirect3D9::CheckDeviceFormat(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) {
	return _hookee->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT hookIDirect3D9::CheckDeviceMultiSampleType(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) {
	return _hookee->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT hookIDirect3D9::CheckDepthStencilMatch(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) {
	return _hookee->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT hookIDirect3D9::CheckDeviceFormatConversion(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat) {
	return _hookee->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT hookIDirect3D9::GetDeviceCaps(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) {
	return _hookee->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR hookIDirect3D9::GetAdapterMonitor(THIS_ UINT Adapter) {
	return _hookee->GetAdapterMonitor(Adapter);
}