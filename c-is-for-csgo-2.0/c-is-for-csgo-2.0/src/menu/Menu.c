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
    menuFont = Surface_CreateFont();
    Surface_SetFontGlyphSet(menuFont, "Tahoma", 13, 400, 0, 0, FONTFLAG_OUTLINE, 0, 0);

    AddMenuBooleanNode(L"Hey I'm first");
    AddMenuBooleanNode(L"I'm second");
    AddMenuBooleanNode(L"Hi mom");
    AddMenuBooleanNode(L"hi dad");
    AddMenuNode(L"I'm bigger", 0.0f, 2.0f, 0.1f);
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

void AddMenuNode(wchar_t *text, float minValue, float maxValue, float stepValue)
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
}

void AddMenuBooleanNode(wchar_t *text)
{
    AddMenuNode(text, 0.0f, 1.0f, 1.0f);
}

void PaintMenu(void)
{
    if (!menuOpened)
        return;

    int y = 7;

    Surface_DrawSetTextFont(menuFont);

    MenuNode *node = menuFrontNode;
    while (node != NULL) {
        wchar_t valueString[16];
        swprintf(valueString, sizeof(valueString), L"%.2f", node->value, node->text);

        if (node == menuSelectedNode) {
            Surface_DrawSetTextColor(255, 128, 128, 255);
        }
        else {
            Surface_DrawSetTextColor(255, 255, 255, 255);
        }

        Surface_DrawSetTextPos(10, y);
        Surface_DrawPrintText(valueString, wcslen(valueString), FONT_DRAW_DEFAULT);

        Surface_DrawSetTextPos(50, y);
        Surface_DrawPrintText(node->text, wcslen(node->text), FONT_DRAW_DEFAULT);

        y += 15;
        node = node->next;
    }
}

BOOL HandleMenuInput(UINT msg, WPARAM wParam, LPARAM lParam)
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