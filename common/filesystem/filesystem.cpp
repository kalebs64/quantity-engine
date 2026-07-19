#include "filesystem.h"
#include "string/stringutil.h"
#include "file.h"
#include <string.h>
#include <unordered_map>
#include <iostream>
#include <Windows.h>


class CFileSystem : public IFileSystem {
public:
    virtual void        InitCommon();
    virtual void        InitCommon(std::string path);

    virtual CFile*     Open(std::string path, uint16 mode);

    virtual bool        FileExists();

    virtual void        MvFile(std::string dest, std::string src);
    virtual void        RmFile(std::string path);

    virtual const char* GetRootPath();
    virtual void        NormalizePath(std::string& path);

    virtual const char* GetExtension(std::string& s);
    virtual void        RemoveExtension(std::string& s);
    virtual void        RemoveRootFromPath(std::string& s);
    virtual void        RemoveBaseFromPath(std::string& s);

    virtual std::string BuildPath(const char* path);
private:
    void                InitRoot();
    bool                IsFullPath(std::string& path);
private:
    std::unordered_map<std::string, std::string> searchPaths;
    std::string         rootPath;
    std::string         baseDir;
};

CFileSystem fsl;
IFileSystem* fileSys = &fsl;

void CFileSystem::InitCommon() {
    InitRoot();
}

void CFileSystem::InitCommon(std::string path) {
    InitRoot();
    baseDir = path;
    std::cout << "Initialized file system" << std::endl;
    std::cout << "$Root: " << rootPath << std::endl;
    std::cout << "$Base: " << baseDir  << std::endl;
}

CFile* CFileSystem::Open(std::string path, uint16 mode) {
    // std::string pp = rootPath + '/' + baseDir + '/' + path;
    std::string pp = BuildPath(path.c_str());

    CFile* file = new CFile(pp.c_str(), mode);

    if(!file) {
        std::cout << "Failed to open " << path << std::endl;
        return nullptr;
    }
    return file;
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

const char* CFileSystem::GetRootPath() {
    return rootPath.c_str();
}

const char* CFileSystem::GetExtension(std::string& s) {
    size_t pos = s.rfind('.');
    std::string str = s.substr(pos, (s.length() - pos));
    return str.c_str();
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

std::string CFileSystem::BuildPath(const char* path) {
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

void* GetFileSystem(const char* version, int* returnCode) {
    return fileSys;
}