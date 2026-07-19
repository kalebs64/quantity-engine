#pragma once

#define CREATEINTERFACE_PROCNAME	"CreateInterface"

//SPEC: should atleast be able to reinterpret the pointer to IAppSystem or a particular derivative
typedef void* (*InterfaceCreateFunc)(const char *name, int *returnValue);
//SPEC: should atleast be able to reinterpret the pointer to IAppSystem or a particular derivative
typedef void* (*InterfaceInstantiationFunc)();

//opaque pointer for hmodule, to reduce how much low level code bleeds into framework
class CModuleHandle;

//opens a dll file and gives pointer to hmodule
CModuleHandle*          LoadModule(const char* name);
//uses CREATEINTERFACE_PROCNAME to extract an interface to IAppSystem
InterfaceCreateFunc     GetInterfaceFactory(CModuleHandle* mdl);