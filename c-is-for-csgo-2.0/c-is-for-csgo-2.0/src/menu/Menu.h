#pragma once
#include <Windows.h>

typedef struct MenuNode_t {
    wchar_t text[64];
    float value;
    float minValue;
    float maxValue;
    float stepValue;
    struct MenuNode_t *previous;
    struct MenuNode_t *next;
} MenuNode;

/*
 * @brief: Initializes the menu, has to be called only once
 */
extern void InitMenu(void);

/*
 * @brief: Uninitializes the menu, has to be called once at the end of the program
 */
extern void UninitMenu(void);

/*
 * @brief: Adds a node to the front of the menu
 */
extern void AddMenuNode(wchar_t *text, float minValue, float maxValue, float stepValue);

/*
 * @brief: Adds a on/off node to the front of the menu
 * @see: AddMenuNode
 */
extern void AddMenuBooleanNode(wchar_t *text);

/*
 * @brief: Paints the menu, has to be called from PaintTraverse
 */
extern void PaintMenu(void);

/*
 * @brief: Handles input to menu
 * @return: If the input should be supressed
 */
extern BOOL HandleMenuInput(UINT msg, WPARAM wParam, LPARAM lParam);