/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#pragma once
#include <Windows.h>

typedef void* HInterface;

/*
 * @brief: Creates a Source Engine interface
 * @return: Pointer to the created interface
 */
extern HInterface CreateInterface(const char *moduleName, const char *interfaceName);

/*
 * @brief: Given an index, gets address of a function from a vtable
 * @return: Address of function at given index
 */
extern inline void *GetVirtualFunction(void *abstractClass, size_t index);