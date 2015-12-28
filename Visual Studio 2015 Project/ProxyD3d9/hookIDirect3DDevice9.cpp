#include "hookIDirect3DDevice9.h"
#include "debug.h"
#include "Drawing.h"
#include "Input.h"
#include <string>

IDirect3DDevice9* hookIDirect3DDevice9::_hookee = NULL;

hookIDirect3DDevice9::hookIDirect3DDevice9(IDirect3DDevice9* hookee)
	:_resetCount(0)
{
	printString("Created d3d9 device hook!");
	_hookee = hookee;
	
	QueryPerformanceCounter(&oldTime);
	QueryPerformanceFrequency(&timeFreq);

	//InitializeAddons();
}

hookIDirect3DDevice9::~hookIDirect3DDevice9(void)
{
	printString("Destroying hookIDirect3DDevice9");
	EndAddons();

	delete _hookee;
}

void hookIDirect3DDevice9::InitializeAddons() {
	printString("Creating addons");
	drawing::initialize(this);
	input::initialize();
	_modManager = new ModManager();
}

void hookIDirect3DDevice9::EndAddons() {
	printString("Destroying addons");

	if (_modManager != NULL) {
		delete _modManager;
		_modManager = NULL;
	}
	//drawing::cleanup();
	//input::cleanup();
}

void hookIDirect3DDevice9::cleanup() {
	printString("Cleaning up hookIDirect3DDevice9");
}

IDirect3DDevice9* hookIDirect3DDevice9::getHookee() {
	return _hookee;
}

HRESULT hookIDirect3DDevice9::Present(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) {
	return _hookee->Present(THIS_   pSourceRect,  pDestRect, hDestWindowOverride,  pDirtyRegion);
}
HRESULT hookIDirect3DDevice9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
    return _hookee->QueryInterface(riid, ppvObj);
}
ULONG hookIDirect3DDevice9::AddRef(THIS) {
    return _hookee->AddRef();
}
ULONG hookIDirect3DDevice9::Release(THIS) {
    //delete addonManager;
	return _hookee->Release();
}
HRESULT hookIDirect3DDevice9::TestCooperativeLevel(THIS) {
    return _hookee->TestCooperativeLevel();
}
HRESULT hookIDirect3DDevice9::EvictManagedResources(THIS) {
    return _hookee->EvictManagedResources();
}
HRESULT hookIDirect3DDevice9::GetDirect3D(THIS_ IDirect3D9** ppD3D9) {
    return _hookee->GetDirect3D(THIS_ ppD3D9);
}
HRESULT hookIDirect3DDevice9::GetDeviceCaps(THIS_ D3DCAPS9* pCaps) {
    return _hookee->GetDeviceCaps(THIS_ pCaps);
}
HRESULT hookIDirect3DDevice9::GetDisplayMode(THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode) {
    return _hookee->GetDisplayMode(THIS_ iSwapChain, pMode);
}
HRESULT hookIDirect3DDevice9::GetCreationParameters(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) {
    return _hookee->GetCreationParameters(THIS_ pParameters);
}
HRESULT hookIDirect3DDevice9::SetCursorProperties(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap) {
    return _hookee->SetCursorProperties(THIS_ XHotSpot, YHotSpot, pCursorBitmap);
}
HRESULT hookIDirect3DDevice9::CreateAdditionalSwapChain(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain) {
    return _hookee->CreateAdditionalSwapChain(THIS_  pPresentationParameters, pSwapChain);
}
HRESULT hookIDirect3DDevice9::GetSwapChain(THIS_ UINT iSwapChain,IDirect3DSwapChain9** pSwapChain) {
    return _hookee->GetSwapChain(THIS_  iSwapChain, pSwapChain);
}
HRESULT hookIDirect3DDevice9::Reset(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) {
	_resetCount++;
	printString("resetting device!");
	EndAddons();
    HRESULT result = _hookee->Reset(THIS_  pPresentationParameters);

	//don't create addons on the first reset. Why? I don't fucking know, but it crashes when doing so on the first reset.
	if (_resetCount >= 2) {
		InitializeAddons();
	}

	//addonManager->ResetDevice();
	return result;
}
HRESULT hookIDirect3DDevice9::GetBackBuffer(THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) {
    return _hookee->GetBackBuffer(THIS_  iSwapChain, iBackBuffer, Type, ppBackBuffer);
}
HRESULT hookIDirect3DDevice9::GetRasterStatus(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) {
    return _hookee->GetRasterStatus(THIS_  iSwapChain, pRasterStatus);
}
HRESULT hookIDirect3DDevice9::SetDialogBoxMode(THIS_ BOOL bEnableDialogs) {
    return _hookee->SetDialogBoxMode(THIS_  bEnableDialogs);
}
HRESULT hookIDirect3DDevice9::CreateTexture(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) {
    return _hookee->CreateTexture(THIS_  Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::CreateVolumeTexture(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* 
pSharedHandle) {
    return _hookee->CreateVolumeTexture(THIS_  Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::CreateCubeTexture(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) {
    return _hookee->CreateCubeTexture(THIS_  EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::CreateVertexBuffer(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) {
    return _hookee->CreateVertexBuffer(THIS_  Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::CreateIndexBuffer(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) {
    return _hookee->CreateIndexBuffer(THIS_  Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::CreateRenderTarget(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** 
ppSurface,HANDLE* pSharedHandle) {
    return _hookee->CreateRenderTarget(THIS_  Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::CreateDepthStencilSurface(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** 
ppSurface,HANDLE* pSharedHandle) {
    return _hookee->CreateDepthStencilSurface(THIS_  Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::UpdateSurface(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) {
    return _hookee->UpdateSurface(THIS_  pSourceSurface,  pSourceRect, pDestinationSurface,  pDestPoint);
}
HRESULT hookIDirect3DDevice9::UpdateTexture(THIS_ IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) {
    return _hookee->UpdateTexture(THIS_  pSourceTexture, pDestinationTexture);
}
HRESULT hookIDirect3DDevice9::GetRenderTargetData(THIS_ IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) {
    return _hookee->GetRenderTargetData(THIS_  pRenderTarget, pDestSurface);
}
HRESULT hookIDirect3DDevice9::GetFrontBufferData(THIS_ UINT iSwapChain,IDirect3DSurface9* pDestSurface) {
    return _hookee->GetFrontBufferData(THIS_  iSwapChain, pDestSurface);
}
HRESULT hookIDirect3DDevice9::StretchRect(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) {
    return _hookee->StretchRect(THIS_  pSourceSurface, pSourceRect, pDestSurface,  pDestRect, Filter);
}
HRESULT hookIDirect3DDevice9::ColorFill(THIS_ IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color) {
    return _hookee->ColorFill(THIS_  pSurface,  pRect, color);
}
HRESULT hookIDirect3DDevice9::CreateOffscreenPlainSurface(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) {
    return _hookee->CreateOffscreenPlainSurface(THIS_ Width, Height, Format, Pool, ppSurface, pSharedHandle);
}
HRESULT hookIDirect3DDevice9::SetRenderTarget(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget) {
    return _hookee->SetRenderTarget(THIS_  RenderTargetIndex, pRenderTarget);
}
HRESULT hookIDirect3DDevice9::GetRenderTarget(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) {
    return _hookee->GetRenderTarget(THIS_  RenderTargetIndex, ppRenderTarget);
}
HRESULT hookIDirect3DDevice9::SetDepthStencilSurface(THIS_ IDirect3DSurface9* pNewZStencil) {
    return _hookee->SetDepthStencilSurface(THIS_  pNewZStencil);
}
HRESULT hookIDirect3DDevice9::GetDepthStencilSurface(THIS_ IDirect3DSurface9** ppZStencilSurface) {
    return _hookee->GetDepthStencilSurface(THIS_  ppZStencilSurface);
}
HRESULT hookIDirect3DDevice9::BeginScene(THIS) {
    return _hookee->BeginScene();
}
HRESULT hookIDirect3DDevice9::EndScene(THIS) {
	
	if (_modManager != NULL) {
		
		D3DVIEWPORT9 viewport;
		GetViewport(&viewport);

		D3DDEVICE_CREATION_PARAMETERS cparams;
		RECT rect;

		GetCreationParameters(&cparams);
		GetClientRect(cparams.hFocusWindow, &rect);
	
		//only draw when the viewport is the same size as the window, ie: we are in the downscaling/upscaling step or if you are playing at 720p just always	
		if (rect.right - rect.left == viewport.Width) {
			LARGE_INTEGER curTime = oldTime;
			LARGE_INTEGER freq;

			QueryPerformanceCounter(&oldTime);
			QueryPerformanceFrequency(&freq);

			float dt = float(oldTime.QuadPart - curTime.QuadPart) / float(freq.QuadPart);
			input::update();

			_modManager->update(dt);
		}
	}
	return _hookee->EndScene();
}
HRESULT hookIDirect3DDevice9::Clear(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) {
    return _hookee->Clear(THIS_  Count,pRects, Flags, Color, Z, Stencil);
}
HRESULT hookIDirect3DDevice9::SetTransform(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) {
    return _hookee->SetTransform(THIS_  State, pMatrix);
}
HRESULT hookIDirect3DDevice9::GetTransform(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) {
    return _hookee->GetTransform(THIS_  State, pMatrix);
}
HRESULT hookIDirect3DDevice9::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE ttt,CONST D3DMATRIX* d3dm) {
    return _hookee->MultiplyTransform(THIS_ ttt, d3dm);
}
HRESULT hookIDirect3DDevice9::SetViewport(THIS_ CONST D3DVIEWPORT9* pViewport) {
    return _hookee->SetViewport(THIS_  pViewport);
}
HRESULT hookIDirect3DDevice9::GetViewport(THIS_ D3DVIEWPORT9* pViewport) {
    return _hookee->GetViewport(THIS_ pViewport);
}
HRESULT hookIDirect3DDevice9::SetMaterial(THIS_ CONST D3DMATERIAL9* pMaterial) {
    return _hookee->SetMaterial(THIS_  pMaterial);
}
HRESULT hookIDirect3DDevice9::GetMaterial(THIS_ D3DMATERIAL9* pMaterial) {
    return _hookee->GetMaterial(THIS_ pMaterial);
}
HRESULT hookIDirect3DDevice9::SetLight(THIS_ DWORD Index,CONST D3DLIGHT9* d3dl) {
    return _hookee->SetLight(THIS_ Index, d3dl);
}
HRESULT hookIDirect3DDevice9::GetLight(THIS_ DWORD Index,D3DLIGHT9* d3dl) {
    return _hookee->GetLight(THIS_ Index,d3dl);
}
HRESULT hookIDirect3DDevice9::LightEnable(THIS_ DWORD Index,BOOL Enable) {
    return _hookee->LightEnable(THIS_  Index, Enable);
}
HRESULT hookIDirect3DDevice9::GetLightEnable(THIS_ DWORD Index,BOOL* pEnable) {
    return _hookee->GetLightEnable(THIS_  Index, pEnable);
}
HRESULT hookIDirect3DDevice9::SetClipPlane(THIS_ DWORD Index,CONST float* pPlane) {
    return _hookee->SetClipPlane(THIS_  Index,  pPlane);
}
HRESULT hookIDirect3DDevice9::GetClipPlane(THIS_ DWORD Index,float* pPlane) {
    return _hookee->GetClipPlane(THIS_  Index, pPlane);
}
HRESULT hookIDirect3DDevice9::SetRenderState(THIS_ D3DRENDERSTATETYPE State,DWORD Value) {
    return _hookee->SetRenderState(THIS_  State, Value);
}
HRESULT hookIDirect3DDevice9::GetRenderState(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue) {
    return _hookee->GetRenderState(THIS_  State, pValue);
}
HRESULT hookIDirect3DDevice9::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) {
    return _hookee->CreateStateBlock(THIS_  Type, ppSB);
}
HRESULT hookIDirect3DDevice9::BeginStateBlock(THIS) {
    return _hookee->BeginStateBlock();
}
HRESULT hookIDirect3DDevice9::EndStateBlock(THIS_ IDirect3DStateBlock9** ppSB) {
    return _hookee->EndStateBlock(THIS_  ppSB);
}
HRESULT hookIDirect3DDevice9::SetClipStatus(THIS_ CONST D3DCLIPSTATUS9* pClipStatus) {
    return _hookee->SetClipStatus(THIS_   pClipStatus);
}
HRESULT hookIDirect3DDevice9::GetClipStatus(THIS_ D3DCLIPSTATUS9* pClipStatus) {
    return _hookee->GetClipStatus(THIS_  pClipStatus);
}
HRESULT hookIDirect3DDevice9::GetTexture(THIS_ DWORD Stage,IDirect3DBaseTexture9** ppTexture) {
    return _hookee->GetTexture(THIS_  Stage, ppTexture);
}
HRESULT hookIDirect3DDevice9::SetTexture(THIS_ DWORD Stage,IDirect3DBaseTexture9* pTexture) {
    return _hookee->SetTexture(THIS_  Stage, pTexture);
}
HRESULT hookIDirect3DDevice9::GetTextureStageState(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) {
    return _hookee->GetTextureStageState(THIS_  Stage, Type, pValue);
}
HRESULT hookIDirect3DDevice9::SetTextureStageState(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) {
    return _hookee->SetTextureStageState(THIS_  Stage, Type, Value);
}
HRESULT hookIDirect3DDevice9::GetSamplerState(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) {
    return _hookee->GetSamplerState(THIS_  Sampler, Type, pValue);
}
HRESULT hookIDirect3DDevice9::SetSamplerState(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) {
    return _hookee->SetSamplerState(THIS_  Sampler, Type, Value);
}
HRESULT hookIDirect3DDevice9::ValidateDevice(THIS_ DWORD* pNumPasses) {
    return _hookee->ValidateDevice(THIS_ pNumPasses);
}
HRESULT hookIDirect3DDevice9::SetPaletteEntries(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries) {
    return _hookee->SetPaletteEntries(THIS_  PaletteNumber,  pEntries);
}
HRESULT hookIDirect3DDevice9::GetPaletteEntries(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries) {
    return _hookee->GetPaletteEntries(THIS_  PaletteNumber, pEntries);
}
HRESULT hookIDirect3DDevice9::SetCurrentTexturePalette(THIS_ UINT PaletteNumber) {
    return _hookee->SetCurrentTexturePalette(THIS_  PaletteNumber);
}
HRESULT hookIDirect3DDevice9::GetCurrentTexturePalette(THIS_ UINT *PaletteNumber) {
    return _hookee->GetCurrentTexturePalette(THIS_  PaletteNumber);
}
HRESULT hookIDirect3DDevice9::SetScissorRect(THIS_ CONST RECT* pRect) {
    return _hookee->SetScissorRect(THIS_   pRect);
}
HRESULT hookIDirect3DDevice9::GetScissorRect(THIS_ RECT* pRect) {
    return _hookee->GetScissorRect(THIS_  pRect);
}
HRESULT hookIDirect3DDevice9::SetSoftwareVertexProcessing(THIS_ BOOL bSoftware) {
    return _hookee->SetSoftwareVertexProcessing(THIS_  bSoftware);
}
HRESULT hookIDirect3DDevice9::SetNPatchMode(THIS_ float nSegments) {
    return _hookee->SetNPatchMode(THIS_  nSegments);
}
HRESULT hookIDirect3DDevice9::DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) {
    return _hookee->DrawPrimitive(THIS_  PrimitiveType, StartVertex, PrimitiveCount);
}
HRESULT hookIDirect3DDevice9::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE d3dp,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) {
    return _hookee->DrawIndexedPrimitive(THIS_ d3dp, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}
HRESULT hookIDirect3DDevice9::DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) {
    return _hookee->DrawPrimitiveUP(THIS_  PrimitiveType, PrimitiveCount, pVertexStreamZeroData,VertexStreamZeroStride);
}
HRESULT hookIDirect3DDevice9::DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT 
IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) {
	return _hookee->DrawIndexedPrimitiveUP(THIS_ PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData,IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}
HRESULT hookIDirect3DDevice9::ProcessVertices(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) {
    return _hookee->ProcessVertices(THIS_  SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}
HRESULT hookIDirect3DDevice9::CreateVertexDeclaration(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) {
    return _hookee->CreateVertexDeclaration(THIS_   pVertexElements, ppDecl);
}
HRESULT hookIDirect3DDevice9::SetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9* pDecl) {
    return _hookee->SetVertexDeclaration(THIS_  pDecl);
}
HRESULT hookIDirect3DDevice9::GetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9** ppDecl) {
    return _hookee->GetVertexDeclaration(THIS_  ppDecl);
}
HRESULT hookIDirect3DDevice9::SetFVF(THIS_ DWORD FVF) {
    return _hookee->SetFVF(THIS_  FVF);
}
HRESULT hookIDirect3DDevice9::GetFVF(THIS_ DWORD* pFVF) {
    return _hookee->GetFVF(THIS_  pFVF);
}
HRESULT hookIDirect3DDevice9::CreateVertexShader(THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) {
    return _hookee->CreateVertexShader(THIS_   pFunction, ppShader);
}
HRESULT hookIDirect3DDevice9::SetVertexShader(THIS_ IDirect3DVertexShader9* pShader) {
    return _hookee->SetVertexShader(THIS_ pShader);
}
HRESULT hookIDirect3DDevice9::GetVertexShader(THIS_ IDirect3DVertexShader9** ppShader) {
    return _hookee->GetVertexShader(THIS_ ppShader);
}
HRESULT hookIDirect3DDevice9::SetVertexShaderConstantF(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) {
    return _hookee->SetVertexShaderConstantF(THIS_  StartRegister,pConstantData, Vector4fCount);
}
HRESULT hookIDirect3DDevice9::GetVertexShaderConstantF(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount) {
    return _hookee->GetVertexShaderConstantF(THIS_  StartRegister, pConstantData, Vector4fCount);
}
HRESULT hookIDirect3DDevice9::SetVertexShaderConstantI(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) {
    return _hookee->SetVertexShaderConstantI(THIS_  StartRegister, pConstantData, Vector4iCount);
}
HRESULT hookIDirect3DDevice9::GetVertexShaderConstantI(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount) {
    return _hookee->GetVertexShaderConstantI(THIS_  StartRegister, pConstantData, Vector4iCount);
}
HRESULT hookIDirect3DDevice9::SetVertexShaderConstantB(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) {
    return _hookee->SetVertexShaderConstantB(THIS_  StartRegister,  pConstantData, BoolCount);
}
HRESULT hookIDirect3DDevice9::GetVertexShaderConstantB(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount) {
    return _hookee->GetVertexShaderConstantB(THIS_ StartRegister, pConstantData, BoolCount);
}
HRESULT hookIDirect3DDevice9::SetStreamSource(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) {
    return _hookee->SetStreamSource(THIS_  StreamNumber, pStreamData, OffsetInBytes, Stride);
}
HRESULT hookIDirect3DDevice9::GetStreamSource(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride) {
    return _hookee->GetStreamSource(THIS_  StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}
HRESULT hookIDirect3DDevice9::SetStreamSourceFreq(THIS_ UINT StreamNumber,UINT Setting) {
    return _hookee->SetStreamSourceFreq(THIS_  StreamNumber, Setting);
}
HRESULT hookIDirect3DDevice9::GetStreamSourceFreq(THIS_ UINT StreamNumber,UINT* pSetting) {
    return _hookee->GetStreamSourceFreq(THIS_  StreamNumber, pSetting);
}
HRESULT hookIDirect3DDevice9::SetIndices(THIS_ IDirect3DIndexBuffer9* pIndexData) {
    return _hookee->SetIndices(THIS_ pIndexData);
}
HRESULT hookIDirect3DDevice9::GetIndices(THIS_ IDirect3DIndexBuffer9** ppIndexData) {
    return _hookee->GetIndices(THIS_  ppIndexData);
}
HRESULT hookIDirect3DDevice9::CreatePixelShader(THIS_ CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) {
    return _hookee->CreatePixelShader(THIS_ pFunction, ppShader);
}
HRESULT hookIDirect3DDevice9::SetPixelShader(THIS_ IDirect3DPixelShader9* pShader) {
    return _hookee->SetPixelShader(THIS_ pShader);
}
HRESULT hookIDirect3DDevice9::GetPixelShader(THIS_ IDirect3DPixelShader9** ppShader) {
    return _hookee->GetPixelShader(THIS_ ppShader);
}
HRESULT hookIDirect3DDevice9::SetPixelShaderConstantF(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) {
    return _hookee->SetPixelShaderConstantF(THIS_  StartRegister, pConstantData, Vector4fCount);
}
HRESULT hookIDirect3DDevice9::GetPixelShaderConstantF(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount) {
    return _hookee->GetPixelShaderConstantF(THIS_  StartRegister, pConstantData, Vector4fCount);
}
HRESULT hookIDirect3DDevice9::SetPixelShaderConstantI(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) {
    return _hookee->SetPixelShaderConstantI(THIS_  StartRegister, pConstantData, Vector4iCount);
}
HRESULT hookIDirect3DDevice9::GetPixelShaderConstantI(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount) {
    return _hookee->GetPixelShaderConstantI(THIS_  StartRegister, pConstantData, Vector4iCount);
}
HRESULT hookIDirect3DDevice9::SetPixelShaderConstantB(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) {
    return _hookee->SetPixelShaderConstantB(THIS_ StartRegister, pConstantData,  BoolCount);
}
HRESULT hookIDirect3DDevice9::GetPixelShaderConstantB(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount) {
    return _hookee->GetPixelShaderConstantB(THIS_ StartRegister, pConstantData, BoolCount);
}
HRESULT hookIDirect3DDevice9::DrawRectPatch(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) {
    return _hookee->DrawRectPatch(THIS_  Handle, pNumSegs, pRectPatchInfo);
}
HRESULT hookIDirect3DDevice9::DrawTriPatch(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) {
    return _hookee->DrawTriPatch(THIS_  Handle, pNumSegs, pTriPatchInfo);
}
HRESULT hookIDirect3DDevice9::DeletePatch(THIS_ UINT Handle) {
    return _hookee->DeletePatch(THIS_  Handle);
}
HRESULT hookIDirect3DDevice9::CreateQuery(THIS_ D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) {
    return _hookee->CreateQuery(THIS_ Type, ppQuery);
}
UINT hookIDirect3DDevice9::GetAvailableTextureMem(THIS) {
    return _hookee->GetAvailableTextureMem();
}
void hookIDirect3DDevice9::SetCursorPosition(THIS_ int X,int Y,DWORD Flags) {
    return _hookee->SetCursorPosition(THIS_  X, Y, Flags);
}
BOOL hookIDirect3DDevice9::ShowCursor(THIS_ BOOL bShow) {
    return _hookee->ShowCursor(THIS_  bShow);
}
UINT hookIDirect3DDevice9::GetNumberOfSwapChains(THIS) {
    return _hookee->GetNumberOfSwapChains();
}
void hookIDirect3DDevice9::SetGammaRamp(THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) {
    return _hookee->SetGammaRamp(THIS_  iSwapChain, Flags, pRamp);
}
void hookIDirect3DDevice9::GetGammaRamp(THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp) {
    return _hookee->GetGammaRamp(THIS_  iSwapChain, pRamp);
}
BOOL hookIDirect3DDevice9::GetSoftwareVertexProcessing(THIS) {
    return _hookee->GetSoftwareVertexProcessing();
}
float hookIDirect3DDevice9::GetNPatchMode(THIS) {
    return _hookee->GetNPatchMode();
}