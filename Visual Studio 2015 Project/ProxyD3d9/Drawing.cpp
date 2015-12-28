#include "Drawing.h"

LPD3DXFONT defaultfont = nullptr;
LPDIRECT3DDEVICE9 defaultdevice = nullptr;

namespace drawing {

	void initialize(LPDIRECT3DDEVICE9 device)
	{
		defaultdevice = device;
		defaultfont = createFont(30, "Arial");
	}

	void cleanup()
	{
		if (defaultfont != nullptr) {
			destroyFont(defaultfont);
			defaultfont = nullptr;
		}
	}

	LPD3DXFONT createFont(int size, const char* fontface)
	{
		LPD3DXFONT font;
		D3DXCreateFont(defaultdevice, size, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontface, &font);
		return font;
	}

	void destroyFont(LPD3DXFONT font)
	{
		font->Release();
	}

	void drawText(const char* text, int x, int y, D3DCOLOR color)
	{
		RECT r{ x, y, 0, 0 };
		defaultfont->DrawTextA(nullptr, text, -1, &r, DT_LEFT | DT_NOCLIP, color);
	}

	void drawText(const char* text, int x, int y, LPD3DXFONT font, D3DCOLOR color)
	{
		RECT r{ x, y, 0, 0 };
		font->DrawTextA(nullptr, text, -1, &r, DT_LEFT | DT_NOCLIP, color);
	}

}