#include "VirtualTableHook.h"
#include <Windows.h>

void Attach(void)
{
	
}

void Detach(void)
{
	
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