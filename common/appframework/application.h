#pragma once
#include "platform/platform.h"
#include "system.h"
#include <vector>

struct appSystemInfo_t {
    const char* interfaceName;
    const char* moduleName;
};

struct appModuleInfo_t {
    CModuleHandle* moduleHandle;
    InterfaceCreateFunc createFunc;
};

class CBaseApplication {
public:
    virtual bool        Create();
    virtual void        Destroy();

    virtual int         OnInit();
    virtual void        OnShutdown();

    virtual int         Main();
public:
    int                 Run();
protected:
    IAppSystem*         AddSystem(CModuleHandle* moduleHandle, const char* interfaceVersion);
    // Add multiple systems at once using system info
    void                AddSystems(appSystemInfo_t* info, int count);
    IAppSystem*         FindSystemAt(int index) {return loadedSystems[index];}
    // Tries to connect all them together
    void                TryConnectAllSystems();
private:
    int                 Init();
    void                Shutdown();

    CModuleHandle*      LoadModuleFromDLL(const char* path);
private:
    std::vector<IAppSystem*> loadedSystems;
    ///all systems come from modules so these should have the same size()
    std::vector<appModuleInfo_t> loadedModules;
};