#include "Surface.h"
#include "Interfaces.h"

void *GetSurface(void)
{
	static void *surface = NULL;
	if (!surface)
		surface = CreateInterface("vguimatsurface", "VGUI_Surface031");

	return surface;
}

void Surface_DrawSetColor(int r, int g, int b, int a)
{
	typedef void(__fastcall *DrawSetColorFn)(void*, void*, int, int, int, int);

	void *surface = GetSurface();

	DrawSetColorFn drawSetColor = GetVirtualFunction(surface, 15);
	drawSetColor(surface, NULL, r, g, b, a);
}

void Surface_DrawSetTextColor(int r, int g, int b, int a)
{
	typedef void(__fastcall *DrawSetTextColorFn)(void*, void*, int, int, int, int);

	void *surface = GetSurface();

	DrawSetTextColorFn drawSetTextColor = GetVirtualFunction(surface, 25);
	drawSetTextColor(surface, NULL, r, g, b, a);
}
																																										 
void Surface_DrawSetTextFont(HFont font)
{
	typedef void(__fastcall *DrawSetTextFontFn)(void*, void*, HFont);

	void *surface = GetSurface();

	DrawSetTextFontFn drawSetTextFont = GetVirtualFunction(surface, 23);
	drawSetTextFont(surface, NULL, font);
}

void Surface_DrawSetTextPos(int x, int y)
{
	typedef void(__fastcall *DrawSetTextPosFn)(void*, void*, int, int);

	void *surface = GetSurface();

	DrawSetTextPosFn drawSetTextPos = GetVirtualFunction(surface, 26);
	drawSetTextPos(surface, NULL, x, y);
}

BOOL Surface_SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int rangeMin, int rangeMax)
{
	typedef BOOL(__fastcall *SetFontGlyphSetFn)(void*, void*, HFont, const char*, int, int, int, int, int, int, int);

	void *surface = GetSurface();

	SetFontGlyphSetFn setFontGlyphSet = GetVirtualFunction(surface, 71);
	return setFontGlyphSet(surface, NULL, font, windowsFontName, tall, weight, blur, scanlines, flags, rangeMin, rangeMax);
}

void Surface_DrawFilledRect(int x0, int y0, int x1, int y1)
{
	typedef void(__fastcall *DrawFilledRectFn)(void*, void*, int, int, int, int);

	void *surface = GetSurface();

	DrawFilledRectFn drawFilledRect = GetVirtualFunction(surface, 16);
	drawFilledRect(surface, NULL, x0, y0, x1, y1);
}

void Surface_DrawOutlinedRect(int x0, int y0, int x1, int y1)
{
	typedef void(__fastcall *DrawOutlinedRectFn)(void*, void*, int, int, int, int);

	void *surface = GetSurface();

	DrawOutlinedRectFn drawOutlinedRect = GetVirtualFunction(surface, 18);
	drawOutlinedRect(surface, NULL, x0, y0, x1, y1);
}

void Surface_DrawLine(int x0, int y0, int x1, int y1)
{
	typedef void(__fastcall *DrawLineFn)(void*, void*, int, int, int, int);

	void *surface = GetSurface();

	DrawLineFn drawLine = GetVirtualFunction(surface, 19);
	drawLine(surface, NULL, x0, y0, x1, y1);
}

void Surface_DrawPrintText(const wchar_t *text, int textLength, FontDrawType_t drawType)
{
	typedef void(__fastcall *DrawPrintTextFn)(void*, void*, const wchar_t*, int, FontDrawType_t);

	void *surface = GetSurface();

	DrawPrintTextFn drawPrintText = GetVirtualFunction(surface, 28);
	drawPrintText(surface, NULL, text, textLength, drawType);
}
																	
void Surface_GetScreenSize(int *wide, int *tall)
{
	typedef void(__fastcall *GetScreenSizeFn)(void*, void*, int*, int*);

	void *surface = GetSurface();

	GetScreenSizeFn getScreenSize = GetVirtualFunction(surface, 44);
	getScreenSize(surface, NULL, wide, tall);
}
																														
HFont Surface_CreateFont(void)
{
	typedef HFont(__fastcall *CreateFontFn)(void*, void*);

	void *surface = GetSurface();

	CreateFontFn createFont = GetVirtualFunction(surface, 70);
	return createFont(surface, NULL);
}