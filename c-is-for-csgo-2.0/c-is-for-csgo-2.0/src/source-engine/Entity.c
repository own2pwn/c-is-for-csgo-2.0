#include "Entity.h"

BOOL IsDormant(HEntity entity)
{
    return *(BOOL*)((DWORD)entity + 0xE9);
}

int GetTeamNum(HEntity entity)
{
    return *(int*)((DWORD)entity + 0xF0);
}

// TODO(szwagi): Make this better
int GetClassId(HEntity entity)
{
    int one = *(int*)((DWORD)entity + 0x8); //IClientNetworkable vtable
    int two = *(int*)(one + 2 * 0x4); //3rd function in the vtable (GetClientClass)
    int three = *(int*)(two + 0x1); //pointer to the ClientClass struct out of the mov eax
    return *(int*)(three + 0x14); //classid
}