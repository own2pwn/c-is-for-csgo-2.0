#include "VirtualTableHook.h"
#include <Windows.h>

void *SwapVirtualTable(void *abstractClass, void *newVirtualTable)
{
	void **virtualTablePointer = abstractClass;

	void *oldVirtualTable = *virtualTablePointer;
	*virtualTablePointer = newVirtualTable;

	return oldVirtualTable;
}

void *GetVirtualTable(void *abstractClass)
{
	return *(void**)abstractClass;
}

void *GetOriginalVirtualTable(void *abstractClass)
{
	void **cloneVirtualTable = GetVirtualTable(abstractClass);

	size_t cloneTableLength = GetVirtualTableLength(cloneVirtualTable);
	cloneTableLength -= 1; // We are storing a pointer to original

	return cloneVirtualTable[cloneTableLength];
}

size_t GetVirtualTableLength(void **virtualTable)
{
	size_t i = 0;
	for (;; ++i) {
		void* function = virtualTable[i];
		if (!function || IsBadCodePtr(function))
			break;
	}

	return i;
}

void InitVirtualTableHook(void *abstractClass)
{
	void **originalVirtualTable = GetVirtualTable(abstractClass);

	size_t originalTableLength = GetVirtualTableLength(originalVirtualTable);
	size_t originalTableSize = originalTableLength * sizeof(void*);

	size_t mallocSize = originalTableSize;
	mallocSize += sizeof(void*); // Extra space for original vtable pointer
	mallocSize += sizeof(void*); // Extra space for null pointer

	void **cloneTable = malloc(mallocSize);
	ZeroMemory(cloneTable, mallocSize);
	memcpy(cloneTable, originalVirtualTable, originalTableSize);

	cloneTable[originalTableLength] = originalVirtualTable; // Store original vtable pointer

	SwapVirtualTable(abstractClass, cloneTable);
}

void UninitVirtualTableHook(void *abstractClass)
{
	void **cloneVirtualTable = GetVirtualTable(abstractClass);

	void **originalVirtualTable = GetOriginalVirtualTable(abstractClass);
	SwapVirtualTable(abstractClass, originalVirtualTable);

	Sleep(100); // TODO: Remove later

	free(cloneVirtualTable);
}

void *HookVirtualTableFunction(void *abstractClass, size_t index, void *newFunction)
{
	void **originalVirtualTable = GetOriginalVirtualTable(abstractClass);
	size_t originalTableLength = GetVirtualTableLength(originalVirtualTable);
	
	if (index > originalTableLength)
		return NULL; // Out of range
	
	void **clonedVirtualTable = GetVirtualTable(abstractClass);
	clonedVirtualTable[index] = newFunction;

	return originalVirtualTable[index];
}