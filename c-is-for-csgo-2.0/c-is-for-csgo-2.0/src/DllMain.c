/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */

#include "DllMain.h"
#include "VirtualTableHook.h"
#include "menu/Menu.h"
#include "source-engine/Surface.h"
#include "source-engine/EntityList.h"
#include "source-engine/Entity.h"
#include "source-engine/BasePlayer.h"
#include "source-engine/ClassIds.h"

void __fastcall HkPaintTraverse(void* panel, void* edx, VPANEL vguiPanel, BOOL forceRepaint, BOOL allowForce)
{
	origPaintTraverse(panel, edx, vguiPanel, forceRepaint, allowForce);

	static VPANEL drawPanel = 0;
	if (!drawPanel && strcmp(GetName(vguiPanel), "MatSystemTopPanel") == 0) {
        drawPanel = vguiPanel;
	}
	else if (vguiPanel == drawPanel) {
        PaintVisuals();
        PaintMenu();
	}
}

void __fastcall HkOnScreenSizeChanged(void *surface, void *edx, int oldWidth, int oldHeight)
{
    origOnScreenSizeChanged(surface, edx, oldWidth, oldHeight);

    MenuOnWindowResize();
}

LRESULT CALLBACK HkWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (MenuOnWindowProc(msg, wParam, lParam)) {
        return 1L;
    }

    return CallWindowProc(origWindowProc, hwnd, msg, wParam, lParam);
}

void PaintVisuals(void)
{
    int highestEntityIndex = GetHighestEntityIndex();
    for (int i = 0; i < highestEntityIndex; ++i) {
        HEntity ent = GetClientEntity(i);
        if (!ent) {
            continue;
        }

        if (IsDormant(ent)) {
            continue;
        }
        
        if (GetClassId(ent) == CLASSID_CSPLAYER) {
            if (GetHealth(ent) <= 0) {
                continue;
            }

        }
    }
}

HANDLE GetGameWindow(void)
{
    static HANDLE gameWindow = NULL;
    if (!gameWindow) {
        gameWindow = FindWindow("Valve001", NULL);
    }

    return gameWindow;
}

void InitHooks(void)
{
    InitVirtualTableHook(GetPanel());
    InitVirtualTableHook(GetSurface());

    origPaintTraverse = HookVirtualTableFunction(GetPanel(), 41, &HkPaintTraverse);
    origOnScreenSizeChanged = HookVirtualTableFunction(GetSurface(), 116, &HkOnScreenSizeChanged);

    // Window proc hook
    origWindowProc = (WNDPROC)GetWindowLongPtr(GetGameWindow(), GWLP_WNDPROC);
    SetWindowLongPtr(GetGameWindow(), GWLP_WNDPROC, (LONG)HkWindowProc);
}

void UninitHooks(void)
{
    SetWindowLongPtr(GetGameWindow(), GWLP_WNDPROC, (LONG)origWindowProc);

    UninitVirtualTableHook(GetSurface());
    UninitVirtualTableHook(GetPanel());
}

void Attach(void)
{
    InitMenu();
    InitHooks();
}

void Detach(void)
{
    UninitHooks();
    UninitMenu();

	FreeConsole();
}

void KeyThread(HINSTANCE instance)
{
    while (!GetAsyncKeyState(VK_F11)) {
        Sleep(50);
    }

	FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	switch(reason) {
	case DLL_PROCESS_ATTACH: {
		AllocConsole();

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);

		Attach();

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyThread, instance, 0, NULL);
        break;
	}
	case DLL_PROCESS_DETACH: {
		Detach();
        break;
	} 
	default: {
        break;
    }
	}
	return TRUE;
}