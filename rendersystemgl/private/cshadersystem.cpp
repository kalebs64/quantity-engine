#include "ishadersystem.h"
#include <ifilesystem.h>
#include <glad/glad.h>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class jkShaderSystemLocal : public jkShaderSystem {
public:
    virtual void    Init();
    virtual void    RegisterFolder(const char* folderName);
    virtual uint    ObtainProgramVariant(const char* vertexPath, const char* fragmentPath, const std::vector<std::string>& defines);
private:
    std::string     ReadFileToString(const std::string& path);
    std::string     ResolveIncludes(const std::string& path, std::unordered_map<std::string, bool>& guards);
    std::string     GenVariantKey(const char* vtxPath, const char* fpsPath, const std::vector<std::string>& defines);

    uint            BuildFromSource(const char* vertexPath, const char* fragmentPath, const std::vector<std::string>& defines);

    std::string     PrepareSourceCode(const char* path, const std::vector<std::string>& defines);

    bool            CompileCheck(uint shader, const char* type);
private:
    std::unordered_map<std::string, uint>   inMemoryShaders;
    const char*     registeredFolder;
};

jkShaderSystemLocal ssl;
jkShaderSystem* g_shaderSystem = &ssl;

void jkShaderSystemLocal::Init() {
    g_fileSystem->RegisterPathAlias("shaderDirectory", "shaders");
}

void jkShaderSystemLocal::RegisterFolder(const char* folderName) {
    if(folderName != nullptr) {
        registeredFolder = folderName;
    }
}

uint jkShaderSystemLocal::ObtainProgramVariant(const char* vertexPath, const char* fragmentPath, const std::vector<std::string>& defines) {
    std::string key = GenVariantKey(vertexPath, fragmentPath, defines);
    
    //Get from memory
    if(inMemoryShaders.count(key)) return inMemoryShaders[key];

    //Get from cache

    //Build it
    uint prog = BuildFromSource(vertexPath, fragmentPath, defines);

    if(prog != 0) {
        //cache it on disk

        //store in memory
        inMemoryShaders[key] = prog;
        //return it too
        return prog;
    }

    //failed
    return 0;
}

std::string jkShaderSystemLocal::ReadFileToString(const std::string& path) {
    // std::string fullPath = registeredFolder;
    // fullPath += '/';
    // fullPath += path;

    // IFile* file = g_fileSystem->Open(fullPath.c_str(), FS_READ);
    IFile* file = g_fileSystem->OpenAtAlias("shaderDirectory", path, FS_READ);
    if (!file || !file->RawHandle()) {
        if (file) delete file;
        return "";
    }

    size_t size = file->GetSize();
    char* buffer = new char[size + 1];
    int readBytes = file->Read(buffer, size);
    buffer[readBytes] = '\0';

    std::string content(buffer);
    delete[] buffer;
    delete file;
    return content;
}

std::string jkShaderSystemLocal::ResolveIncludes(const std::string& path, std::unordered_map<std::string, bool>& guards) {
    //This file was already copied into the shader
    if(guards[path]) return "";
    guards[path] = true;

    std::string src = ReadFileToString(path);

    std::string out;

    size_t pos = 0;
    size_t prev = 0;

    while((pos = src.find('\n', prev)) != std::string::npos) {
        std::string line = src.substr(prev, pos - prev);
        prev = pos + 1;

        size_t includePos = line.find("#include");
    
        if(includePos != std::string::npos) {
            size_t first = line.find('\"');
            size_t last = line.find_last_of('\"');

            // if(first != std::string::npos && last != std::string::npos) {
            //     std::string incPath = "shaders/" + line.substr(first + 1, last - first - 1);
            //     out += ResolveIncludes(incPath, guards) + "\n";
            // }
            if(first != std::string::npos && last != std::string::npos) {
                std::string incPath = line.substr(first + 1, last - first - 1); 
                out += ResolveIncludes(incPath, guards) + "\n";
            }
        }
        else if(line.find("#version") == std::string::npos) {
            out += line + "\n";
        }
    }

    if (prev < src.size()) {
        std::string line = src.substr(prev);
        if (line.find("#version") == std::string::npos && line.find("#include") == std::string::npos) {
            out += line;
        }
    }
    return out;
}

std::string jkShaderSystemLocal::GenVariantKey(const char* vtxPath, const char* fpsPath, const std::vector<std::string>& defines) {
    std::string s = vtxPath;
    s += fpsPath;

    for (auto& x : defines) s += x;
    return s;
}

uint jkShaderSystemLocal::BuildFromSource(const char* vertexPath, const char* fragmentPath, const std::vector<std::string>& defines) {
    std::string vSrc = PrepareSourceCode(vertexPath, defines);
    std::string fSrc = PrepareSourceCode(fragmentPath, defines);

    const char* vPtr = vSrc.c_str();
    const char* fPtr = fSrc.c_str();

    uint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vPtr, NULL);
    CompileCheck(vs, "vertex_shader_46");

    uint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fPtr, NULL);
    CompileCheck(fs, "fragment_shader_46");

    uint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glProgramParameteri(prog, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
    glLinkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

std::string jkShaderSystemLocal::PrepareSourceCode(const char* path, const std::vector<std::string>& defines) {
    std::unordered_map<std::string, bool> guards;
    
    std::string resolvedCode = ResolveIncludes(path, guards);

    std::string finalSrc = "#version 460 core\n";
    for (const auto& d : defines) {
        finalSrc += "#define " + d + "\n";
    }

    finalSrc += resolvedCode;
    return finalSrc;
}

bool jkShaderSystemLocal::CompileCheck(uint shader, const char* type) {
    GLint compiled;
    glCompileShader(shader);

    char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "(engine) failed to compile shader, type: '%s'\n %s\n", type, infoLog);
        return false;
    };
    return true;
}