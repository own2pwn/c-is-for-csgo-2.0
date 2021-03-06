/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */

#include "Interface.h"

HInterface CreateInterface(const char *moduleName, const char *interfaceName)
{
	typedef void*(*CreateInterfaceFn)(const char*, int*);

	HMODULE module = GetModuleHandle(moduleName);
	FARPROC proc = GetProcAddress(module, "CreateInterface");
	CreateInterfaceFn factory = (CreateInterfaceFn)proc;
	return factory(interfaceName, NULL);
}

inline void *GetVirtualFunction(void *abstractClass, size_t index)
{
	void **vtable = *(void***)abstractClass;
	return vtable[index];
}