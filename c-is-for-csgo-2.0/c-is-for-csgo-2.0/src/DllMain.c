/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#include "VirtualTableHook.h"
#include "source-engine/Surface.h"
#include "source-engine/Panel.h"
#include "menu/Menu.h"
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
void __fastcall HkPaintTraverse(void* panel, void* edx, VPANEL vguiPanel, BOOL forceRepaint, BOOL allowForce)
{
	origPaintTraverse(panel, edx, vguiPanel, forceRepaint, allowForce);

	static VPANEL drawPanel = 0;
	if (!drawPanel && strcmp(Panel_GetName(vguiPanel), "MatSystemTopPanel") == 0) {
        drawPanel = vguiPanel;
	}
	else if (vguiPanel == drawPanel) {
        PaintMenu();
	}
}

/*
 * @brief: OnScreenSizeChanged hook
 */
void __fastcall HkOnScreenSizeChanged(void *surface, void *edx, int oldWidth, int oldHeight)
{
    origOnScreenSizeChanged(surface, edx, oldWidth, oldHeight);

    MenuOnWindowResize();
}

/*
 * @brief: Window procedure hook
 */
LRESULT CALLBACK HkWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (MenuOnWindowProc(msg, wParam, lParam))
        return 1L;

    return CallWindowProc(origWindowProc, hwnd, msg, wParam, lParam);
}

/* 
 * @brief: Gets the game window
 */
HANDLE GetGameWindow()
{
    static HANDLE gameWindow = NULL;
    if (!gameWindow) {
        gameWindow = FindWindow("Valve001", NULL);
    }

    return gameWindow;
}

/*
 * @brief: Initializes all the hooks
 */
void InitHooks()
{
    InitVirtualTableHook(GetPanel());
    InitVirtualTableHook(GetSurface());

    origPaintTraverse = HookVirtualTableFunction(GetPanel(), 41, &HkPaintTraverse);
    origOnScreenSizeChanged = HookVirtualTableFunction(GetSurface(), 116, &HkOnScreenSizeChanged);

    // Window proc hook
    origWindowProc = (WNDPROC)GetWindowLongPtr(GetGameWindow(), GWLP_WNDPROC);
    SetWindowLongPtr(GetGameWindow(), GWLP_WNDPROC, (LONG)HkWindowProc);
}

/*
 * @brief: Uninitializes all the hooks
 */
void UninitHooks()
{
    SetWindowLongPtr(GetGameWindow(), GWLP_WNDPROC, (LONG)origWindowProc);

    UninitVirtualTableHook(GetSurface());
    UninitVirtualTableHook(GetPanel());
}

/*
 * @brief: Handles attaching, everything should be initialized here
 */
void Attach(void)
{
    InitMenu();
    InitHooks();
}

/*
 * @brief: Handles detaching, everything should uninitialized here
 */
void Detach(void)
{
    UninitHooks();
    UninitMenu();

	FreeConsole();
}

/*
 * @brief: Handles panic button
 * @todo(szwagi): should be deleted later
 */
void KeyThread(HINSTANCE instance)
{
	while (!GetAsyncKeyState(VK_F11))
		Sleep(50);

	FreeLibraryAndExitThread(instance, 0);
}

/*
 * @brief: Handles the module entry
 * @return: Weather it succeeded or not
 */
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	switch(reason) {
	case DLL_PROCESS_ATTACH:
    {
		AllocConsole();

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);

		Attach();

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyThread, instance, 0, NULL);
	} break;
	case DLL_PROCESS_DETACH:
	{
		Detach();
	} break;
	default: break;
	}
	return TRUE;
}