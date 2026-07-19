#pragma once
#include "types.h"
#include <string>

class jkFileWriter {};

class CFile;

class IFileSystem {
public:
    virtual void        InitCommon() = 0;
    virtual void        InitCommon(std::string path) = 0;

    virtual CFile*      Open(std::string path, uint16 mode) = 0;

    virtual bool        FileExists() = 0;

    virtual void        MvFile(std::string dest, std::string src) = 0;
    virtual void        RmFile(std::string path) = 0;

    virtual const char* GetRootPath() = 0;
    virtual void        NormalizePath(std::string& path) = 0;

    virtual const char* GetExtension(std::string& s) = 0;
    virtual void        RemoveExtension(std::string& s) = 0;
    //This is assuming you have a root
    virtual void        RemoveRootFromPath(std::string& s) = 0;
    //This is assuming you have already removed the root
    virtual void        RemoveBaseFromPath(std::string& s) = 0;

    virtual std::string BuildPath(const char* path) = 0;
};

extern IFileSystem* fileSys;

void* GetFileSystem(const char* version, int* returnCode);