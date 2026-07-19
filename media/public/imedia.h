#pragma once
#include "iwindow.h"
#include <appframework/appframework.h>

class IMedia : public IAppSystem {
public:
    //IAppSystem

    virtual sysInitValue_t      Init() = 0;
    virtual void                Shutdown() = 0;
    virtual bool                ConnectThroughFactory(InterfaceCreateFunc factory) = 0;
    virtual void*               QueryInterface(const char* interfaceName) = 0;
public:
    virtual IWindow*            CreateWindow(mediaWindowInfo_t* info) = 0;
    virtual IWindow*            GetTargetWindow() = 0;
    virtual void                Poll() = 0;
    virtual bool                CloseRequested() = 0;
};

#define QUANTITY_MEDIA_VERSION "QUANTITY_MEDIA_001"
extern IMedia* g_media;