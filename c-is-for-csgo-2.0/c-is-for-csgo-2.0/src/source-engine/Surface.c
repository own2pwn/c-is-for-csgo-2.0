/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#include "Surface.h"

inline HInterface GetSurface(void)
{
	static HInterface surface = NULL;
    if (!surface) {
        surface = CreateInterface("vguimatsurface", "VGUI_Surface031");
    }

	return surface;
}

void DrawSetColor(int r, int g, int b, int a)
{
	typedef void(__fastcall *DrawSetColorFn)(HInterface, void*, int, int, int, int);

    HInterface surface = GetSurface();

	DrawSetColorFn drawSetColor = GetVirtualFunction(surface, 15);
	drawSetColor(surface, NULL, r, g, b, a);
}

void DrawSetTextColor(int r, int g, int b, int a)
{
	typedef void(__fastcall *DrawSetTextColorFn)(HInterface, void*, int, int, int, int);

    HInterface surface = GetSurface();

	DrawSetTextColorFn drawSetTextColor = GetVirtualFunction(surface, 25);
	drawSetTextColor(surface, NULL, r, g, b, a);
}
																																										 
void DrawSetTextFont(HFont font)
{
	typedef void(__fastcall *DrawSetTextFontFn)(HInterface, void*, HFont);

    HInterface surface = GetSurface();

	DrawSetTextFontFn drawSetTextFont = GetVirtualFunction(surface, 23);
	drawSetTextFont(surface, NULL, font);
}

void DrawSetTextPos(int x, int y)
{
	typedef void(__fastcall *DrawSetTextPosFn)(HInterface, void*, int, int);

    HInterface surface = GetSurface();

	DrawSetTextPosFn drawSetTextPos = GetVirtualFunction(surface, 26);
	drawSetTextPos(surface, NULL, x, y);
}

BOOL SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int rangeMin, int rangeMax)
{
	typedef BOOL(__fastcall *SetFontGlyphSetFn)(HInterface, void*, HFont, const char*, int, int, int, int, int, int, int);

    HInterface surface = GetSurface();

	SetFontGlyphSetFn setFontGlyphSet = GetVirtualFunction(surface, 72);
	return setFontGlyphSet(surface, NULL, font, windowsFontName, tall, weight, blur, scanlines, flags, rangeMin, rangeMax);
}

void DrawFilledRect(int x0, int y0, int x1, int y1)
{
	typedef void(__fastcall *DrawFilledRectFn)(HInterface, void*, int, int, int, int);

    HInterface surface = GetSurface();

	DrawFilledRectFn drawFilledRect = GetVirtualFunction(surface, 16);
	drawFilledRect(surface, NULL, x0, y0, x1, y1);
}

void DrawOutlinedRect(int x0, int y0, int x1, int y1)
{
	typedef void(__fastcall *DrawOutlinedRectFn)(HInterface, void*, int, int, int, int);

    HInterface surface = GetSurface();

	DrawOutlinedRectFn drawOutlinedRect = GetVirtualFunction(surface, 18);
	drawOutlinedRect(surface, NULL, x0, y0, x1, y1);
}

void DrawLine(int x0, int y0, int x1, int y1)
{
	typedef void(__fastcall *DrawLineFn)(HInterface, void*, int, int, int, int);

    HInterface surface = GetSurface();

	DrawLineFn drawLine = GetVirtualFunction(surface, 19);
	drawLine(surface, NULL, x0, y0, x1, y1);
}

void DrawPrintText(const wchar_t *text, int textLength, FontDrawType_t drawType)
{
	typedef void(__fastcall *DrawPrintTextFn)(HInterface, void*, const wchar_t*, int, FontDrawType_t);

    HInterface surface = GetSurface();

	DrawPrintTextFn drawPrintText = GetVirtualFunction(surface, 28);
	drawPrintText(surface, NULL, text, textLength, drawType);
}
																	
void GetScreenSize(int *wide, int *tall)
{
	typedef void(__fastcall *GetScreenSizeFn)(HInterface, void*, int*, int*);

    HInterface surface = GetSurface();

	GetScreenSizeFn getScreenSize = GetVirtualFunction(surface, 44);
	getScreenSize(surface, NULL, wide, tall);
}
																														
HFont CreateFont(void)
{
	typedef HFont(__fastcall *CreateFontFn)(HInterface, void*);

    HInterface surface = GetSurface();

	CreateFontFn createFont = GetVirtualFunction(surface, 71);
	return createFont(surface, NULL);
}