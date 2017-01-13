#include "Menu.h"
#include "../source-engine/Surface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * @brief: Determines weather the menu is opened or not
 */
BOOL menuOpened = TRUE;

/*
 * @brief: Font that the menu is using
 */
HFont menuFont;

/*
 * @brief: The first node
 */
MenuNode *menuFrontNode = NULL;

/*
 * @brief: The highlighted node that will take the input
 */
MenuNode *menuSelectedNode = NULL;



void InitMenu(void)
{
    menuFont = CreateFont();
    SetFontGlyphSet(menuFont, "Tahoma", 13, 400, 0, 0, FONTFLAG_OUTLINE, 0, 0);
}

void UninitMenu(void)
{
    MenuNode *node = menuFrontNode;
    while (node != NULL) {
        MenuNode* next = node->next;

        free(node);

        node = next;
    }
}

MenuNode *AddMenuNode(wchar_t *text, float minValue, float maxValue, float stepValue)
{
    MenuNode *link = malloc(sizeof(MenuNode));
    ZeroMemory(link, sizeof(MenuNode));

    wcscpy_s(link->text, sizeof(link->text) / sizeof(wchar_t), text);

    link->value = minValue;
    link->minValue = minValue;
    link->maxValue = maxValue;
    link->stepValue = stepValue;

    link->next = menuFrontNode;

    if (menuFrontNode) {
        menuFrontNode->previous = link;
    }

    menuFrontNode = link;
    menuSelectedNode = menuFrontNode;

    return link;
}

MenuNode *AddMenuBooleanNode(wchar_t *text)
{
    return AddMenuNode(text, 0.0f, 1.0f, 1.0f);
}

void PaintMenu(void)
{
    if (!menuOpened)
        return;

    int y = 7;

    DrawSetTextFont(menuFont);

    MenuNode *node = menuFrontNode;
    while (node != NULL) {
        wchar_t valueString[8];
        swprintf(valueString, sizeof(valueString) / sizeof(wchar_t), L"%.2f", node->value);

        if (node == menuSelectedNode) {
            DrawSetTextColor(255, 128, 128, 255);
        }
        else {
            DrawSetTextColor(255, 255, 255, 255);
        }

        DrawSetTextPos(10, y);
        DrawPrintText(valueString, wcslen(valueString), FONT_DRAW_DEFAULT);

        DrawSetTextPos(50, y);
        DrawPrintText(node->text, wcslen(node->text), FONT_DRAW_DEFAULT);

        y += 15;
        node = node->next;
    }
}

BOOL MenuOnWindowProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (!menuSelectedNode)
        return FALSE;

    switch (msg) {
    case WM_KEYDOWN:
    {
        if(wParam == VK_END) {
            menuOpened = !menuOpened;
        }

        if (menuOpened) {
            if (wParam == VK_DOWN) {
                if (menuSelectedNode->next) {
                    menuSelectedNode = menuSelectedNode->next;
                }
                return TRUE;
            }
            else if (wParam == VK_UP) {
                if (menuSelectedNode->previous) {
                    menuSelectedNode = menuSelectedNode->previous;
                }
                return TRUE;
            }
            else if (wParam == VK_LEFT) {
                menuSelectedNode->value = max(menuSelectedNode->minValue, menuSelectedNode->value - menuSelectedNode->stepValue);
                return TRUE;
            }
            else if (wParam == VK_RIGHT) {
                menuSelectedNode->value = min(menuSelectedNode->maxValue, menuSelectedNode->value + menuSelectedNode->stepValue);
                return TRUE;
            }
        }
    } break;
    default: break;
    }

    return FALSE;
}

void MenuOnWindowResize(void)
{
    SetFontGlyphSet(menuFont, "Tahoma", 13, 400, 0, 0, FONTFLAG_OUTLINE, 0, 0);
}

BOOL GetMenuBooleanValue(MenuNode *node)
{
    return node->value != 0.0f;
}