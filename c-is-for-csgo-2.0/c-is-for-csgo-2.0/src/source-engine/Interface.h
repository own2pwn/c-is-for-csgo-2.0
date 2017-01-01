#pragma once
#include <Windows.h>

/*
 * @brief: Creates a Source Engine interface
 * @return: Pointer to the created interface
 */
extern void *CreateInterface(const char *moduleName, const char *interfaceName);

/*
 * @brief: Given an index, gets address of a function from a vtable
 * @return: Address of function at given index
 */
extern void *GetVirtualFunction(void *abstractClass, size_t index);