#pragma once

#include <d3d9.h>
#include <d3dx9.h>

namespace drawing {
	void initialize(LPDIRECT3DDEVICE9 device);
	void cleanup();
	LPD3DXFONT createFont(int size, const char* fontface = "Arial");
	void destroyFont(LPD3DXFONT font);
	void drawText(const char* text, int x, int y, D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255));
	void drawText(const char* text, int x, int y, LPD3DXFONT font, D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255));
}
