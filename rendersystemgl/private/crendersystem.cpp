#include "irendersystem.h"
#include "ishadersystem.h"
#include "irenderworld.h"
#include <ifilesystem.h>
#include <imedia.h>
#include <glad/glad.h>

IFileSystem* g_fileSystem;
IMedia* g_media;

class CRenderSystemOpenGL : public IRenderSystemOpenGL {
public:
    //IAppSystem

    virtual sysInitValue_t      Init();
    virtual void                Shutdown();
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory);
    virtual void*               QueryInterface(const char* interfaceName);
public:
    virtual void                SetCurrentRenderRect(int width, int height);
    virtual void                Frame();
};

CRenderSystemOpenGL gl;
IRenderSystemOpenGL* g_renderSystemGL = &gl;

sysInitValue_t CRenderSystemOpenGL::Init() {
    IWindow* wnd = g_media->GetTargetWindow();

    if(wnd) {
        wnd->InitGL();

        if(gladLoadGLLoader(wnd->GetProcAddress())) {
            SetCurrentRenderRect(wnd->GetWidth(), wnd->GetHeight());

            g_shaderSystem->Init();

            return SYS_INIT_OK;
        }
    }
}

void CRenderSystemOpenGL::Shutdown() {}

bool CRenderSystemOpenGL::ConnectThroughFactory(InterfaceCreateFunc factory) {
    int i = 0;

    if(!g_media && factory) {
        g_media = (IMedia*)(factory(QUANTITY_MEDIA_VERSION, &i));
        if(g_media) return true;
    }
    if(!g_fileSystem && factory) {
        g_fileSystem = (IFileSystem*)(factory(QUANTITY_FILESYSTEM_VERSION, &i));
        if(g_fileSystem) return true;
    }
    return false;
}

void* CRenderSystemOpenGL::QueryInterface(const char* interfaceName) {
    if(strcmp(interfaceName, QUANTITY_SHADERSYSTEM_VERSION)) {
        return g_shaderSystem;
    }
    else if(strcmp(interfaceName, QUANTITY_RENDERWORLD_VERSION) == 0) {
        return g_renderWorld;
    }
    return nullptr;
}

void CRenderSystemOpenGL::SetCurrentRenderRect(int width, int height) {
    if(width > 0 && height > 0) {
        glViewport(0, 0, width, height);
    }
}

void CRenderSystemOpenGL::Frame() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    g_renderWorld->Frame();
}

DLL_FUNC_EXPORT void* CreateInterface(const char *name, int *returnValue) {
    if(strcmp(name, QUANTITY_RENDERSYSTEMGL_VERSION) == 0) {
        *returnValue = 0;
        return g_renderSystemGL;
    }
    *returnValue = -1;
    return nullptr;
}