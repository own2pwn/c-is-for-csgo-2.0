/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#pragma once
#include <stdio.h>

/*
 * @brief: Swaps virtual tables
 * @return: Original virtual table
 */
extern void *SwapVirtualTable(void *abstractClass, void *newVirtualTable);

/*
 * @brief: Gets the virtual table of an interface
 * @return: The virtual table pointer
 */
extern void *GetVirtualTable(void *abstractClass);

/*
* @brief: Gets the original virtual table, has to be called while hook is initialized
* @return: The original virtual table pointer
*/
extern void *GetOriginalVirtualTable(void *abstractClass);

/*
 * @brief: Gets the length of a virtual table
 * @return: Amount of pointers in the virtual table
 */
extern size_t GetVirtualTableLength(void **virtualTable);

/*
 * @brief: Initializes the hook, has to be called only once
 */
extern void InitVirtualTableHook(void *abstractClass);

/*
 * @brief: Uninitializes the hook, has to be called only once
 */
extern void UninitVirtualTableHook(void *abstractClass);

/*
 * @brief: Hooks the virtual table function, has to be called while hook is initialized
 * @return: The original function pointer
 */
extern void *HookVirtualTableFunction(void *abstractClass, size_t index, void *newFunction);