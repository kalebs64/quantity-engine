#pragma once
#include <types.h>

union SDL_Event;
constexpr uint32 IN_FORWARD       = 1 << 0;
constexpr uint32 IN_BACKWARD      = 1 << 1;
constexpr uint32 IN_LEFT          = 1 << 2;
constexpr uint32 IN_RIGHT         = 1 << 3;
constexpr uint32 IN_JUMP          = 1 << 4;
constexpr uint32 IN_DOWN          = 1 << 5;
constexpr uint32 IN_ATTACK        = 1 << 6;
constexpr uint32 IN_ALT_ATTACK    = 1 << 7;

struct userCmd_t {
    float               m_forwardMove = 0.0f; 
    float               m_sideMove = 0.0f;    

    float               m_mouseDeltaX = 0.0f;
    float               m_mouseDeltaY = 0.0f;
    float               m_mouseX = 0.0f;
    float               m_mouseY = 0.0f;

    uint32              m_buttons = 0;
};


class IInputSystem {
public:
    virtual void        TranslateEvent(SDL_Event* pEvent) = 0;

    virtual void        BindKey(int pScancode, uint32 pButtonBit) = 0;
    virtual void        BindMouse(uint8 pMouseButton, uint32 pButtonBit) = 0;

    virtual userCmd_t   UserCommand() = 0;
    virtual bool        RequestedQuit() = 0;

    virtual void        HandleScanCode(int pCode, bool pPressed) = 0;
    virtual void        HandleMouseButton(uint8 pCode, bool pPressed) = 0;
    virtual void        HandleMouseMotion(float pX, float pY) = 0;
    virtual void        SetMouseAccumulation(float pDeltaX, float pDeltaY) = 0;
};

#define QUANTITY_INPUTSYSTEM_VERSION "QUANTITY_INPUTSYSTEM_001"
extern IInputSystem* g_inputSystem;