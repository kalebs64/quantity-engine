#pragma once
#include "platform/platform.h"
#include "interface.h"

#define SYSTEM_DECLARATION(interfaceClass, interfaceName)                                           \
extern interfaceClass* interfaceName;

#define SYSTEM_DEFINITION(interfaceClass, interfaceName, implementationClass)                       \
implementationClass impl;                                                                           \
interfaceClass* interfaceName = &impl;

#if 0
SYSTEM_DECLARATION(IAppSystem, appSystem)
class CMaterialSystem : public IAppSystem {
public:
    virtual void                Init();
    virtual void                Shutdown();
    virtual void                ProvidePointers();
};
SYSTEM_DEFINITION(IAppSystem, appSystem, CAppSystem, "ENGINE_APP_SYSTEM_001")
#endif

enum sysInitValue_t : int {
    SYS_INIT_OK = 0,
    SYS_INIT_FAILED,
    SYS_INIT_COUNT,
};
//TODO: MOVE FILESYSTEM TO A MODULE SO ITS NOT DUPLICATED AS EVERY MODULE LIKELY NEEDS COMMON.LIB

stripped_vclass IAppSystem {
public:
    virtual sysInitValue_t      Init() = 0;
    virtual void                Shutdown() = 0;

    //Connect an interface to this system so it can have access to it without needing to duplicate it in memory. NOTE this is completely implementation dependent this will try to cast the factory func's results to an expected type so do connect systems knowing that's what the other system wants, or don't.
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory) = 0;
    virtual void*               QueryInterface(const char* interfaceName) = 0;
};