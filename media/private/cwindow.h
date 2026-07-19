#pragma once
#include "iwindow.h"
#include <SDL3/SDL.h>

class CWindow : public IWindow {
public:
    virtual bool                    Init(mediaWindowInfo_t* info);
    virtual bool                    InitGL();
    virtual void                    Shutdown();
    virtual void                    UpdateScreen();
    virtual bool                    CloseRequested();
    virtual int                     GetWidth() {return m_width;}
    virtual int                     GetHeight() {return m_height;}
    virtual COpenGLContext*         GetGLContext();
    virtual GLProcLoaderFunc        GetProcAddress();
private:
    int                             m_width;
    int                             m_height;
    const char*                     m_title;

    SDL_Window*                     m_window;
    SDL_GLContext                   m_glContext;
};