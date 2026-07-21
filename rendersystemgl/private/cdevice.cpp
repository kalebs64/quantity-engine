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
    virtual uint                CreateShaderPipeline(uint* shaders, int count);
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
    GLint compiled;

    uint8 glType;
    switch(type) {
        case QRST_VERTEX: glType = GL_VERTEX_SHADER; break;
        case QRST_FRAGMENT: glType = GL_FRAGMENT_SHADER; break;
        case QRST_COMPUTE: glType = GL_COMPUTE_SHADER; break;
        case QRST_GEOMETRY: glType = GL_GEOMETRY_SHADER; break;
        case QRST_TESSELATOR: glType = GL_TESS_CONTROL_SHADER; break;
    }
    uint shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    if(compiled) {
        // fprintf(stderr, "(engine) failed to compile shader, type: '%s'\n %s\n", type, infoLog);
        return shader;
    };


    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    return 0;
}

uint CRenderDevice::CreateShaderPipeline(uint* shaders, int count) {
    uint out;

    out = glCreateProgram();

    for(int i = 0; i < count; ++i) {
        if(shaders[i] > 0) {
            glAttachShader(out, shaders[i]);
        }
    }

    glLinkProgram(out);
    return out;
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