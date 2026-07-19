#pragma once
#include <types.h>
#include "ifile.h"
#include <appframework/appframework.h>
#include <string>

stripped_vclass IFileSystem : public IAppSystem {
public:
    //IAppSystem

    virtual sysInitValue_t      Init() = 0;
    virtual void                Shutdown() = 0;
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory) = 0;
    virtual void*               QueryInterface(const char* interfaceName) = 0;
public:
    virtual void                InitAndSetBase(std::string path) = 0;

    //The paths are to be virtual so basically just 'shaders/'
    virtual void                RegisterPathAlias(std::string aliasName, std::string path) = 0;

    virtual IFile*              Open(std::string path, uint16 mode) = 0;
    virtual IFile*              OpenAtAlias(std::string aliasName, std::string path, uint16 mode) = 0;

    virtual bool                FileExists() = 0;
    virtual void                MvFile(std::string dest, std::string src) = 0;
    virtual void                RmFile(std::string path) = 0;
    virtual void                RemoveExtension(std::string& s) = 0;

    //This is assuming you have a root
    virtual void                RemoveRootFromPath(std::string& s) = 0;
    //This is assuming you have already removed the root
    virtual void                RemoveBaseFromPath(std::string& s) = 0;
    virtual void                NormalizePath(std::string& path) = 0;
    virtual std::string         BuildPath(std::string path) = 0;

    virtual std::string         GetRootPath() = 0;
    virtual std::string         GetExtension(std::string& s) = 0;
};

#define QUANTITY_FILESYSTEM_VERSION "QUANTITY_FILESYSTEM_002"
extern IFileSystem* g_fileSystem;