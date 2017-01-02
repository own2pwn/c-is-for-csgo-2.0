#include "VirtualTableHook.h"
#include "source-engine/Surface.h"
#include "source-engine/Panel.h"
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
		Surface_DrawSetColor(255, 0, 0, 255);
		Surface_DrawFilledRect(10, 10, 50, 100);
	}
}

// ------------

void Attach(void)
{
	InitVirtualTableHook(GetPanel());
	OrigPaintTraverse = HookVirtualTableFunction(GetPanel(), 41, HkPaintTraverse);
}

void Detach(void)
{
	UninitVirtualTableHook(GetPanel());

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