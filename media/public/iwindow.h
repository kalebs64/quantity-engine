#pragma once
#include <types.h>

//opaque classes for public use of implemented handles
class CWindowHandle;
class CProcAdressHandle;
class COpenGLContext;

using                               GLProcLoaderFunc = void*(*)(const char*);

constexpr uint32 MD_WND_USING_GL        = 1 << 0;
constexpr uint32 MD_WND_MINIMIZED       = 1 << 1;
constexpr uint32 MD_WND_MAXIMIZED       = 1 << 2;
constexpr uint32 MD_WND_FULLSCREENED    = 1 << 3;

struct mediaWindowInfo_t {
    int width;
    int height;
    uint32 flags;
    const char* title;
};

class IWindow {
public:
    virtual                         ~IWindow() = default;

    virtual bool                    Init(mediaWindowInfo_t* info) = 0;
    virtual bool                    InitGL() = 0;
    virtual void                    Shutdown() = 0;

    virtual void                    UpdateScreen() = 0;
    virtual bool                    CloseRequested() = 0;

    virtual int                     GetWidth() = 0;
    virtual int                     GetHeight() = 0;

    virtual COpenGLContext*         GetGLContext() = 0;
    virtual GLProcLoaderFunc        GetProcAddress() = 0;
};