/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */

#pragma once
#include "source-engine/Panel.h"
#include <Windows.h>

/*
 * @brief: Typedefs of functions that we hook
 */
typedef void(__fastcall *PaintTraverseFn)(void*, void*, VPANEL, BOOL, BOOL);
typedef void(__fastcall *OnScreenSizeChangedFn)(void*, void*, int, int);

/*
 * @brief: The originals of functions that we hook
 */
PaintTraverseFn origPaintTraverse = NULL;
OnScreenSizeChangedFn origOnScreenSizeChanged = NULL;
WNDPROC origWindowProc = NULL;

/*
 * @brief: PaintTraverse hook, everything is drawn here
 */
extern void __fastcall HkPaintTraverse(void* panel, void* edx, VPANEL vguiPanel, BOOL forceRepaint, BOOL allowForce);

/*
 * @brief: OnScreenSizeChanged hook
 */
extern void __fastcall HkOnScreenSizeChanged(void *surface, void *edx, int oldWidth, int oldHeight);

/*
 * @brief: Window procedure hook
 */
extern LRESULT CALLBACK HkWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
 * @brief: Paints the visual cheats
 */
extern void PaintVisuals(void);

/*
 * @brief: Gets the game window
 */
extern HANDLE GetGameWindow(void);

/*
 * @brief: Initializes all the hooks
 */
extern void InitHooks(void);

/*
 * @brief: Uninitializes all the hooks
 */
extern void UninitHooks(void);

/*
 * @brief: Handles attaching, everything should be initialized here
 */
extern void Attach(void);

/*
 * @brief: Handles detaching, everything should uninitialized here
 */
extern void Detach(void);

/*
 * @brief: Handles panic button
 * @todo(szwagi): should be deleted later
 */
extern void KeyThread(HINSTANCE instance);

/*
 * @brief: Handles the module entry
 * @return: Weather it succeeded or not
 */
extern BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved);