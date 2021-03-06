/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#pragma once
#include "Interface.h"
#include <Windows.h>

#ifdef CreateFont
#undef CreateFont
#endif

typedef unsigned long HFont;

typedef enum {
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
} FontDrawType_t;

typedef enum {
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
} FontFlags_t;

/*
* @return: Pointer to Source Engine Surface interface
*/
extern inline HInterface GetSurface(void);

/*
 * @brief: Sets draw color, does not affect text
 * @see: Surface_DrawSetTextColor
 */
extern void DrawSetColor(int r, int g, int b, int a);

/*
* @brief: Sets text draw color
*/
extern void DrawSetTextColor(int r, int g, int b, int a);

/*
 * @brief: Sets the font used to render text
 */
extern void DrawSetTextFont(HFont font);

/*
 * @brief: Sets where the text will be rendered
 */
extern void DrawSetTextPos(int x, int y);

/*
 * @brief: Sets a font glyph set to a given font
 * @return: Weather it succeeded or not
 * @see: Surface_CreateFont
 */
extern BOOL SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int rangeMin /* 0 */, int rangeMax /* 0 */);

/*
 * @brief: Draws a filled rectangle
 * @see: Surface_DrawSetColor
 */
extern void DrawFilledRect(int x0, int y0, int x1, int y1);

/*
 * @brief: Draws an outlined rectangle
 * @see: Surface_DrawSetColor
 */
extern void DrawOutlinedRect(int x0, int y0, int x1, int y1);

/*
 * @brief: Draws a line
 * @see: Surface_DrawSetColor
 */
extern void DrawLine(int x0, int y0, int x1, int y1);

/*
 * @brief: Draws given text
 * @see: Surface_DrawSetTextFont, Surface_DrawSetTextColor, Surface_DrawSetTextPos
 */
extern void DrawPrintText(const wchar_t *text, int textLength, FontDrawType_t drawType /* FONT_DRAW_DEFAULT*/);

/*
 * @brief: Gets the resolution the game is currently running at
 */
extern void GetScreenSize(int *wide, int *tall);

/*
 * @brief: Creates a new font handle
 * @see: Surface_SetFontGlyphSet
 */
extern HFont CreateFont(void);