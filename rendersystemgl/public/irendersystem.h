#pragma once
#include <appframework/appframework.h>

class IRenderSystemOpenGL : public IAppSystem {
public:
    //IAppSystem

    virtual sysInitValue_t      Init() = 0;
    virtual void                Shutdown() = 0;
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory) = 0;
    virtual void*               QueryInterface(const char* interfaceName) = 0;
public:
    virtual void                Frame() = 0;
};

#define QUANTITY_RENDERSYSTEMGL_VERSION "QUANTITY_RENDERSYSTEMGL_001"
extern IRenderSystemOpenGL* g_renderSystemGL;