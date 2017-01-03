/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */

#include "Panel.h"
#include <Windows.h>

inline HInterface GetPanel(void)
{
    static HInterface panel = NULL;
    if (!panel) {
        panel = CreateInterface("vgui2.dll", "VGUI_Panel009");
    }

    return panel;
}

const char *Panel_GetName(VPANEL vpanel)
{
    typedef const char*(__fastcall *GetNameFn)(HInterface, void*, VPANEL);

    HInterface panel = GetPanel();

    GetNameFn getName = GetVirtualFunction(panel, 36);
    return getName(panel, NULL, vpanel);
}