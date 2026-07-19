#include "interface.h"
#include "filesystem/filesystem.h"
#include <Windows.h>
#include <string>

CModuleHandle* LoadModule(const char* name) {
    std::string search = fileSys->GetRootPath();
#ifdef _WIN32
    HMODULE dll;

    //try root/name
    search += '/';
    search += name;

    dll = LoadLibraryA(search.c_str());

    if(!dll) {
        //try root/base/bin/name
        search.clear();
        search += "bin" + '/';
        search += name;
        search = fileSys->BuildPath(search.c_str());

        dll = LoadLibraryA(search.c_str());
    }

    if(dll) {
        return reinterpret_cast<CModuleHandle*>(dll);
    }
#endif
    return nullptr;
}

InterfaceCreateFunc GetInterfaceFactory(CModuleHandle* mdl) {
    if(!mdl) return nullptr;
#ifdef _WIN32
    HMODULE dll = reinterpret_cast<HMODULE>(mdl);

    if(dll) {
        return reinterpret_cast<InterfaceCreateFunc>(GetProcAddress(dll, CREATEINTERFACE_PROCNAME));
    }
    return nullptr;
#elif defined(POSIX)
    //I don't remember how linux handles this
    return nullptr;
#endif
}