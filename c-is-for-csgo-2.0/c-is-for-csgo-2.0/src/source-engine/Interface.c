#include "Interface.h"

void *CreateInterface(const char *moduleName, const char *interfaceName)
{
	typedef void*(*CreateInterfaceFn)(const char*, int*);

	HMODULE module = GetModuleHandle(moduleName);
	FARPROC proc = GetProcAddress(module, "CreateInterface");
	CreateInterfaceFn factory = (CreateInterfaceFn)proc;
	return factory(interfaceName, NULL);
}

void *GetVirtualFunction(void *abstractClass, size_t index)
{
	void **vtable = *(void***)abstractClass;
	return vtable[index];
}