/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#include "VirtualTableHook.h"
#include "source-engine/Surface.h"
#include "source-engine/Panel.h"
#include "menu/Menu.h"
#include <Windows.h>

// Tests for now

typedef void(__fastcall *PaintTraverseFn)(void*, void*, VPANEL, BOOL, BOOL);

PaintTraverseFn OrigPaintTraverse = NULL;

void __fastcall HkPaintTraverse(void* panel, void* edx, VPANEL vguiPanel, BOOL forceRepaint, BOOL allowForce)
{
	OrigPaintTraverse(panel, edx, vguiPanel, forceRepaint, allowForce);

	static VPANEL drawPanel = 0;
	if (!drawPanel && strcmp(Panel_GetName(vguiPanel), "MatSystemTopPanel") == 0) {
        drawPanel = vguiPanel;
	}
	else if (vguiPanel == drawPanel) {
        PaintMenu();
	}
}

WNDPROC origWindowProc = NULL;
LRESULT CALLBACK HkWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (HandleMenuInput(msg, wParam, lParam))
        return 1L;

    return CallWindowProc(origWindowProc, hwnd, msg, wParam, lParam);
}

// ------------

void Attach(void)
{
    InitMenu();

    HANDLE window = FindWindow(NULL, "Counter-Strike: Global Offensive");
    origWindowProc = (WNDPROC)GetWindowLongPtr(window, GWLP_WNDPROC);
    SetWindowLongPtr(window, GWLP_WNDPROC, (LONG)HkWindowProc);

	InitVirtualTableHook(GetPanel());
	OrigPaintTraverse = HookVirtualTableFunction(GetPanel(), 41, HkPaintTraverse);
}

void Detach(void)
{
	UninitVirtualTableHook(GetPanel());

    UninitMenu();

    HANDLE window = FindWindow(NULL, "Counter-Strike: Global Offensive");
    SetWindowLongPtr(window, GWLP_WNDPROC, (LONG)origWindowProc);

	FreeConsole();
}

void KeyThread(HINSTANCE instance)
{
	while (!GetAsyncKeyState(VK_F11))
		Sleep(50);

	FreeLibraryAndExitThread(instance, 0);
}

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