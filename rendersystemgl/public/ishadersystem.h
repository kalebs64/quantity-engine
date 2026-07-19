#pragma once
#include <types.h>
#include <string>
#include <vector>

class jkShaderSystem {
public:
    virtual void        Init() = 0;
    virtual void        RegisterFolder(const char* folderName) = 0;

    //Will either: Fetch from memory, load from cache, or load and compile from disk
    virtual uint        ObtainProgramVariant(const char* vertexPath, const char* fragmentPath, const std::vector<std::string>& defines) = 0;
    // virtual uint        ObtainComputeProgram(const char* computeName, const std::vector<std::string>& defines) = 0;
};

#define QUANTITY_SHADERSYSTEM_VERSION "QUANTITY_SHADERSYSTEM_002"
extern jkShaderSystem* g_shaderSystem;