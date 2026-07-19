#include "imedia.h"
#include "cwindow.h"
#include <ifilesystem.h>

DLL_FUNC_EXPORT void* CreateInterface(const char *name, int *returnValue);

IFileSystem* g_fileSystem;

class CMedia : public IMedia {
public:
    virtual sysInitValue_t      Init();
    virtual void                Shutdown();
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory);
    virtual void*               QueryInterface(const char* interfaceName);
public:
    virtual IWindow*            CreateWindow(mediaWindowInfo_t* info);
    virtual IWindow*            GetTargetWindow();
    virtual void                Poll();
    virtual bool                CloseRequested();
private:
    bool                        m_closeRequest;
    IWindow*                    m_window;
};

CMedia mediaImpl;
IMedia* g_media = &mediaImpl;

sysInitValue_t CMedia::Init() {
    m_closeRequest = false;
    m_window = nullptr;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    return SYS_INIT_OK;
}

void CMedia::Shutdown() {
}

bool CMedia::ConnectThroughFactory(InterfaceCreateFunc factory) {
    int i = 0;

    if(factory == CreateInterface) {
        return false;
    }

    if(!g_fileSystem) {
        g_fileSystem = (IFileSystem*)factory(QUANTITY_FILESYSTEM_VERSION, &i);
    }

    if(i > -1) return true;

    return false;
}

void* CMedia::QueryInterface(const char* interfaceName) {
    if(strcmp(interfaceName, QUANTITY_FILESYSTEM_VERSION) == 0) {
        return g_fileSystem;
    }
    return nullptr;
}

IWindow* CMedia::CreateWindow(mediaWindowInfo_t* info) {
    if(info) {
        m_window = new CWindow();

        if(m_window && m_window->Init(info)) {
            return m_window;
        }
    }
    return nullptr;
}

IWindow* CMedia::GetTargetWindow() {
    return m_window;
}

void CMedia::Poll() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                m_closeRequest = true;
                break;
        }
    }
}

bool CMedia::CloseRequested() {
    return m_closeRequest;
}

DLL_FUNC_EXPORT void* CreateInterface(const char *name, int *returnValue) {
    if(strcmp(name, QUANTITY_MEDIA_VERSION) == 0) {
        *returnValue = 0;
        return g_media;
    }
    *returnValue = -1;
    return nullptr;
}