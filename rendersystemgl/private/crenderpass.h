#pragma once

class CRenderPass {
public:
    virtual                     ~CRenderPass() = default;

    virtual void                Init();
    virtual void                Frame();

    void                        UpdateRenderRect(int width, int height);
private:
    int                         m_rectWidth;
    int                         m_rectHeight;

    const char*                 m_passName;
};