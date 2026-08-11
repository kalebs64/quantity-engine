#include "iinputsystem.h"

class CInputSystem : public IInputSystem {
public:
    virtual void        TranslateEvent(SDL_Event* pEvent);
    virtual void        BindKey(int pScancode, uint32 pButtonBit);
    virtual void        BindMouse(uint8 pMouseButton, uint32 pButtonBit);
    virtual userCmd_t   UserCommand();
    virtual bool        RequestedQuit();
    virtual void        HandleScanCode(int pCode, bool pPressed);
    virtual void        HandleMouseButton(uint8 pCode, bool pPressed);
    virtual void        HandleMouseMotion(float pX, float pY);
    virtual void        SetMouseAccumulation(float pDeltaX, float pDeltaY);
};

CInputSystem cis;
IInputSystem* g_inputSystem = &cis;

void CInputSystem::TranslateEvent(SDL_Event* pEvent) {

}

void CInputSystem::BindKey(int pScancode, uint32 pButtonBit) {

}

void CInputSystem::BindMouse(uint8 pMouseButton, uint32 pButtonBit) {

}

userCmd_t CInputSystem::UserCommand() {
    userCmd_t cmd;
    return cmd;
}

bool CInputSystem::RequestedQuit() {
    return false;
}

void CInputSystem::HandleScanCode(int pCode, bool pPressed) {

}

void CInputSystem::HandleMouseButton(uint8 pCode, bool pPressed) {

}

void CInputSystem::HandleMouseMotion(float pX, float pY) {

}

void CInputSystem::SetMouseAccumulation(float pDeltaX, float pDeltaY) {

}