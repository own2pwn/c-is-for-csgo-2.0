#include "Panel.h"
#include "Interfaces.h"
#include <Windows.h>

void *GetPanel()
{
	static void *panel = NULL;
	if (!panel)
		panel = CreateInterface("vgui2.dll", "VGUI_Panel009");

	return panel;
}

const char *Panel_GetName(VPANEL vpanel)
{
	typedef const char*(__fastcall *GetNameFn)(void*, void*, VPANEL);

	void *panel = GetPanel();

	GetNameFn getName = GetVirtualFunction(panel, 36);
	return getName(panel, NULL, vpanel);
}