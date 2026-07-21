#include "idevice.h"
#include <glad/glad.h>

class CRenderDevice : public IRenderDevice {
public:
    virtual void                Init();
    virtual void                Shutdown();
    virtual uint                CreateRenderTarget();
    virtual void                SetRenderTarget(uint target);
    virtual void                AttachTextureToRenderTarget(uint texture, uint8 attachPoint);
    virtual void                DestroyRenderTarget(uint target);
    virtual void                RenderTargetSetColor(float r, float g, float b, float a);
    virtual void                RenderTargetSetColorArray(float* rgba);
    virtual void                RenderTargetClear(uint8 targets);
    virtual uint                CreateShader(uint8 type, char* sourceCode);
    virtual uint                CreateShaderPipeline(uint* shaders);
    virtual void                SetShaderPipeline(uint pipeline);
    virtual uint                CreateBuffer(uint8 type, uint8 flags);
    virtual uint                CreateMappedBuffer();
    virtual uint                CreateTexture(int width, int height, uint32 format, byte_t* data);
    virtual void                DestroyTexture(uint texture);
    virtual void                DrawIndexedInstancedIndirect(uint bufferForArgs);
    virtual void                Flush();
};

CRenderDevice backend;
IRenderDevice* g_renderDevice = &backend;

uint CRenderDevice::CreateRenderTarget() {
    uint out;
    glGenFramebuffers(1, &out);
    return out;
}

void CRenderDevice::SetRenderTarget(uint target) {
    glBindFramebuffer(GL_FRAMEBUFFER, target);
}

void CRenderDevice::AttachTextureToRenderTarget(uint texture, uint8 attachPoint) {
    uint8 glFormat;

    switch(attachPoint) {
        case QTAP_COLOR:    glFormat |= GL_COLOR_ATTACHMENT0; break;
        case QTAP_DEPTH:    glFormat |= GL_DEPTH_ATTACHMENT; break;
        case QTAP_STENCIL:  glFormat |= GL_STENCIL_ATTACHMENT; break;
        default: break;
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, glFormat, GL_TEXTURE_2D, texture, 0);
}

void CRenderDevice::DestroyRenderTarget(uint target) {
    glDeleteFramebuffers(1, &target);
}

void CRenderDevice::RenderTargetSetColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void CRenderDevice::RenderTargetSetColorArray(float* rgba) {
    RenderTargetSetColor(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void CRenderDevice::RenderTargetClear(uint8 targets) {
    uint8 glFormat;
    if(targets & RDCT_COLOR) {
        glFormat |= GL_COLOR_BUFFER_BIT;
    }
    if(targets & RDCT_DEPTH) {
        glFormat |= GL_DEPTH_BUFFER_BIT;
    }
    if(targets & RDCT_STENCIL) {
        glFormat |= GL_STENCIL_BUFFER_BIT;
    }
    glClear(glFormat);
}

uint CRenderDevice::CreateShader(uint8 type, char* sourceCode) {
    return 0;
}

uint CRenderDevice::CreateShaderPipeline(uint* shaders) {
    return 0;
}

void CRenderDevice::SetShaderPipeline(uint pipeline) {}

uint CRenderDevice::CreateBuffer(uint8 type, uint8 flags) {
    return 0;
}

uint CRenderDevice::CreateMappedBuffer() {
    return 0;
}

uint CRenderDevice::CreateTexture(int width, int height, uint32 format, byte_t* data) {
    return 0;
}

void CRenderDevice::DestroyTexture(uint texture) {
}

void CRenderDevice::DrawIndexedInstancedIndirect(uint bufferForArgs) {
}

void CRenderDevice::Flush() {
    glFlush();
}