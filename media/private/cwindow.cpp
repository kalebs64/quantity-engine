#include "cwindow.h"

static void* SDL3GladAddr(const char* name) {
    return reinterpret_cast<void*>(SDL_GL_GetProcAddress(name));
}

bool CWindow::Init(mediaWindowInfo_t* info) {
    SDL_WindowFlags wndFlags = 0;

    if(info->flags & MD_WND_USING_GL) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        wndFlags |= SDL_WINDOW_OPENGL;
    }

    if(info->flags & MD_WND_MAXIMIZED) {
        wndFlags |= SDL_WINDOW_MAXIMIZED;
    }

    if(info->flags & MD_WND_MINIMIZED) {
        wndFlags |= SDL_WINDOW_MINIMIZED;
    }

    if(info->flags & MD_WND_FULLSCREENED) {
        wndFlags |= SDL_WINDOW_FULLSCREEN;
    }

    m_window = SDL_CreateWindow(info->title, info->width, info->height, wndFlags);
    m_width = info->width;
    m_height = info->height;
    m_title = info->title;

    if(m_window) {
        return true;
    }
    return false;
}

bool CWindow::InitGL() {
    m_glContext = SDL_GL_CreateContext(m_window);
    if(m_glContext) {
        SDL_GL_MakeCurrent(m_window, m_glContext);
        return true;
    }
    return false;
}

void CWindow::Shutdown() {}

void CWindow::UpdateScreen() {
    SDL_GL_SwapWindow(m_window);
}

bool CWindow::CloseRequested() {
    return false;
}

COpenGLContext* CWindow::GetGLContext() {
    return reinterpret_cast<COpenGLContext*>(m_glContext);
}

GLProcLoaderFunc CWindow::GetProcAddress() {
    return SDL3GladAddr;
}