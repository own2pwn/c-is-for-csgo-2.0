#include "BasePlayer.h"
#include <Windows.h>

int GetHealth(HBasePlayer basePlayer)
{
    return *(int*)((DWORD)basePlayer + 0xFC);
}

unsigned int GetFlags(HBasePlayer basePlayer)
{
    return *(unsigned int*)((DWORD)basePlayer + 0x100);
}