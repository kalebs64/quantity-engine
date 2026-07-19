#include "ifilesystem.h"
#include "ifile.h"
#include "cfile.h"
#include <string/stringutil.h>
#include <string.h>
#include <unordered_map>
#include <iostream>
#include <Windows.h>

struct pathAlias_t {
    std::string name;
    std::string path;
};

class CFileSystem : public IFileSystem {
public:
    virtual sysInitValue_t      Init();
    virtual void                Shutdown();
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory);
    virtual void*               QueryInterface(const char* interfaceName);

public:
    virtual void                InitAndSetBase(std::string path);
    virtual void                RegisterPathAlias(std::string aliasName, std::string path);

    virtual IFile*              Open(std::string path, uint16 mode);
    virtual IFile*              OpenAtAlias(std::string aliasName, std::string path, uint16 mode);

    virtual bool                FileExists();
    virtual void                MvFile(std::string dest, std::string src);
    virtual void                RmFile(std::string path);
    virtual void                RemoveExtension(std::string& s);

    virtual void                RemoveRootFromPath(std::string& s);
    virtual void                RemoveBaseFromPath(std::string& s);
    virtual void                NormalizePath(std::string& path);
    virtual std::string         BuildPath(std::string path);

    virtual std::string         GetRootPath();
    virtual std::string         GetExtension(std::string& s);
private:
    void                        InitRoot();
    bool                        IsFullPath(std::string& path);
private:
    std::unordered_map<std::string, std::string> aliases;
    std::string                 rootPath;
    std::string                 baseDir;
};

CFileSystem fsl;
IFileSystem* g_fileSystem = &fsl;

sysInitValue_t CFileSystem::Init() {
    return SYS_INIT_OK;
}

void CFileSystem::Shutdown() {
    //TODO: IMPLEMENT
}

bool CFileSystem::ConnectThroughFactory(InterfaceCreateFunc factory) {
    //CFileSystem needs no connections
    return true;
}

void* CFileSystem::QueryInterface(const char* interfaceName) {
    //CFileSystem has nothing to give
    return nullptr;
}

void CFileSystem::InitAndSetBase(std::string path) {
    InitRoot();
    baseDir = path;
    std::cout << "Initialized file system" << std::endl;
    std::cout << "$Root: " << rootPath << std::endl;
    std::cout << "$Base: " << baseDir  << std::endl;
}

void CFileSystem::RegisterPathAlias(std::string aliasName, std::string path) {
    aliases[aliasName] = path;

    std::cout << "registered path alias for '" << path << "' as '" << aliasName << "'" << std::endl;
}

IFile* CFileSystem::Open(std::string path, uint16 mode) {
    // std::string pp = rootPath + '/' + baseDir + '/' + path;
    std::string pp = BuildPath(path);

    CBaseFile* file = new CBaseFile();

    if(!file) {
        std::cout << "failed to open " << path << std::endl;
        return nullptr;
    }

    file->Open(path.c_str(), mode);
    return file;
}

IFile* CFileSystem::OpenAtAlias(std::string aliasName, std::string path, uint16 mode) {
    std::string al = aliases[aliasName];
    if(!al.empty()) {
        std::string pp = al + "/" + path;

        return Open(pp, mode);
    }
    return nullptr;
}

bool CFileSystem::FileExists() {
    return false;
}

void CFileSystem::MvFile(std::string dest, std::string src) {}

void CFileSystem::RmFile(std::string path) {}

void CFileSystem::NormalizePath(std::string& path) {
    for(int i = 0; i < path.size(); ++i) {
        if(path[i] == '\\') path[i] = '/';
    }
}

std::string CFileSystem::GetRootPath() {
    return rootPath;
}

std::string CFileSystem::GetExtension(std::string& s) {
    size_t pos = s.rfind('.');
    std::string str = s.substr(pos, (s.length() - pos));
    return str;
}

void CFileSystem::RemoveExtension(std::string& s) {
    size_t pos = s.rfind('.');

    s.erase(pos);
}

void CFileSystem::RemoveRootFromPath(std::string& s) {
    s.erase(0, rootPath.size()+1);
}

void CFileSystem::RemoveBaseFromPath(std::string& s) {
    s.erase(0, baseDir.size()+1);
}

std::string CFileSystem::BuildPath(std::string path) {
    if(IsFullPath(baseDir)) {
        return baseDir + '/' + path;
    }
    return rootPath + '/' + baseDir + '/' + path;
}

void CFileSystem::InitRoot() {
#ifdef _WIN32
    wchar_t buffer[MAX_PATH];
    DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    if (len == 0 || len >= MAX_PATH) {
        rootPath = "";
        return;
    }

    wchar_t* p = wcsrchr(buffer, L'\\');
    if (!p) {
        rootPath = "";
        return;
    }
    *p = L'\0';

    rootPath = UTF16To8(buffer);

    NormalizePath(rootPath);
#endif
}

bool CFileSystem::IsFullPath(std::string& path) {
    if(isalpha(path[0]) && path[1] == ':') return true;
    if (path.length() >= 2 && path[0] == '\\' && path[1] == '\\') {
        return true;
    }
    return false;
}


DLL_FUNC_EXPORT void* CreateInterface(const char *name, int *returnValue) {
    if(strcmp(name, QUANTITY_FILESYSTEM_VERSION) == 0) {
        *returnValue = 0;
        return g_fileSystem;
    }
    *returnValue = -1;
    return nullptr;
}