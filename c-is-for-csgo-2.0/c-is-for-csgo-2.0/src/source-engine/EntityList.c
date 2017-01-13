/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#include "EntityList.h"
#include <Windows.h>

inline HInterface GetEntityList(void)
{
    static HInterface entityList = NULL;
    if (!entityList) {
        entityList = CreateInterface("client.dll", "VClientEntityList003");
    }

    return entityList;
}

HEntity GetEntity(int index)
{
    typedef HEntity(__fastcall *GetEntityFn)(HInterface, void*, int);

    HInterface entityList = GetEntityList();

    GetEntityFn getEntity = GetVirtualFunction(entityList, 3);
    return getEntity(entityList, NULL, index);
}