#include "Menu.h"
#include "../source-engine/Surface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//HFont menuFont;
MenuNode *frontNode = NULL;

void InitMenu(void)
{
   // menuFont = Surface_CreateFont();
    //Surface_SetFontGlyphSet(menuFont, "Tahoma", 13, 800, 0, 0, FONTFLAG_OUTLINE, 0, 0);

    AddMenuBooleanNode(L"1");
    AddMenuBooleanNode(L"2");
    AddMenuBooleanNode(L"3");
    AddMenuBooleanNode(L"4");
    AddMenuBooleanNode(L"5");
}

void UninitMenu(void)
{
    MenuNode *node = frontNode;
    while (node != NULL) {
        MenuNode* next = node->next;

        free(node);

        node = next;
    }
}

void AddMenuNode(wchar_t *text, float minValue, float maxValue, float stepValue)
{
    MenuNode *link = malloc(sizeof(MenuNode));

    wcscpy_s(link->text, sizeof(link->text) / sizeof(wchar_t), text);

    link->minValue = minValue;
    link->maxValue = maxValue;
    link->stepValue = stepValue;

    link->next = frontNode;
    frontNode = link;
}

void AddMenuBooleanNode(wchar_t *text)
{
    AddMenuNode(text, 0.0f, 1.0f, 1.0f);
}

void PaintMenu(void)
{
    int x = 20;
    int y = 10;

    Surface_DrawSetTextFont(0x77);
    Surface_DrawSetTextColor(255, 255, 255, 255);

    MenuNode *node = frontNode;
    while(node != NULL) {
        // paint it here
        Surface_DrawSetTextPos(x, y);
        Surface_DrawPrintText(node->text, wcslen(node->text), FONT_DRAW_DEFAULT);

        y += 14;
        node = node->next;
    }
}