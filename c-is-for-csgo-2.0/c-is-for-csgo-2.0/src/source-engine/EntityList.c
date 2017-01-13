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

HEntity GetClientEntity(int index)
{
    typedef HEntity(__fastcall *GetClientEntityFn)(HInterface, void*, int);

    HInterface entityList = GetEntityList();

    GetClientEntityFn getClientEntity = GetVirtualFunction(entityList, 3);
    return getClientEntity(entityList, NULL, index);
}

int GetHighestEntityIndex(void)
{
    typedef int(__fastcall *GetHighestEntityIndexFn)(HInterface);

    HInterface entityList = GetEntityList();

    GetHighestEntityIndexFn getHighestEntityIndex = GetVirtualFunction(entityList, 6);
    return getHighestEntityIndex(entityList);
}