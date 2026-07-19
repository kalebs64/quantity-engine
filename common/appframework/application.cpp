#include "application.h"
#include <Windows.h>
#include <iostream>

bool CBaseApplication::Create() {
    return false;
}

void CBaseApplication::Destroy() {}

int CBaseApplication::OnInit() {
    return 0;
}

void CBaseApplication::OnShutdown() {}

int CBaseApplication::Main() {
    return 0;
}

int CBaseApplication::Run() {
    int returnValue = 0;

    if(!Create()) {
        //we failed during creation.
        return -1;
    }

    TryConnectAllSystems();

    returnValue = Init();

    if(returnValue > 0) {
        //we failed during initialization.
        return returnValue;
    }

    returnValue = Main();

    Shutdown();

    return returnValue;
}

IAppSystem* CBaseApplication::AddSystem(CModuleHandle* moduleHandle, const char* interfaceVersion) {
    HMODULE mod = reinterpret_cast<HMODULE>(moduleHandle);

    if(mod) {
        InterfaceCreateFunc fn = reinterpret_cast<InterfaceCreateFunc>(GetProcAddress(mod, CREATEINTERFACE_PROCNAME));
        if(fn) {
            int i = 0;
            IAppSystem* sys = static_cast<IAppSystem*>(fn(interfaceVersion, &i));

            if(sys) {
                appModuleInfo_t info = {};
                info.createFunc = fn;
                info.moduleHandle = reinterpret_cast<CModuleHandle*>(mod);
                loadedModules.push_back(info);
                return sys;
            }
            std::cout << "error didn't get an interface from create function." << std::endl;
        }
        std::cout << "error failed to find interface create function." << std::endl;
    }
    std::cout << "error failed to load module." << std::endl;
    return nullptr;
}

void CBaseApplication::AddSystems(appSystemInfo_t* info, int count) {
    for(int i = 0; i < count; ++i) {
        CModuleHandle* hnd = LoadModuleFromDLL(info[i].moduleName);

        if(hnd) {
            IAppSystem* sys = AddSystem(hnd, info[i].interfaceName);

            loadedSystems.push_back(sys);
        }
    }
}

int CBaseApplication::Init() {
    int i = 0;
    i = OnInit();

    return i;
}

void CBaseApplication::Shutdown() {
    OnShutdown();

    //shutdown systems
    for(int i = 0; i < loadedSystems.size(); ++i) {
        IAppSystem* system = loadedSystems[i];

        if(system) {
            system->Shutdown();
        }
    }

    //dispose of all modules
}

CModuleHandle* CBaseApplication::LoadModuleFromDLL(const char* path) {
    // char szCwd[1024];

    // getcwd(szCwd, sizeof(szCwd));

    HMODULE mdl = LoadLibraryA(path);

    if(mdl) {
        CModuleHandle* handle = reinterpret_cast<CModuleHandle*>(mdl);
        return handle;
    }
    return nullptr;
}

void CBaseApplication::TryConnectAllSystems() {
    // for(int i = 0; i < loadedModules.size(); ++i) {
    //     appModuleInfo_t* currMod = &loadedModules[i];

    //     for(int j = 0; j < loadedModules.size(); ++j) {
    //         if(currMod != &loadedModules[j]) {
    //             loadedSystems[i]->ConnectThroughFactory(currMod->createFunc);
    //         }
    //     }
    // }
    for(int i = 0; i < loadedSystems.size(); ++i) {
        IAppSystem* sys = loadedSystems[i];

        for(int j = 0; j < loadedModules.size(); ++j) {
            sys->ConnectThroughFactory(loadedModules[j].createFunc);
        }
    }
}