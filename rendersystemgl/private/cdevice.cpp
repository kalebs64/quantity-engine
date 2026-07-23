#include "idevice.h"
#include <glad/glad.h>

class CRenderDevice : public IRenderDevice {
public:
    virtual void                Init();
    virtual void                Shutdown();
    virtual uint                CreateRenderTarget();
    virtual void                SetRenderTarget(uint target);
    virtual void                AttachTextureToRenderTarget(uint target, uint texture, uint8 attachPoint);
    virtual void                DestroyRenderTarget(uint target);
    virtual void                RenderTargetSetColor(float r, float g, float b, float a);
    virtual void                RenderTargetSetColorArray(float* rgba);
    virtual void                RenderTargetClear(uint target, uint8 bufferTarget, float r, float g, float b);
    virtual uint                CreateShader(uint8 type, char* sourceCode);
    virtual uint                CreateShaderPipeline(uint* shaders, int count);
    virtual void                SetShaderPipeline(uint pipeline);
    virtual void                DispatchComputePipeline(uint groupsX, uint groupsY, uint groupsZ);
    virtual uint                CreateBuffer(uint8 type, uint8 flags, size_t sizePerElement, int elementCount);
    virtual void                PushDataIntoBuffer(uint buffer, size_t sizeOfData, void* data);
    virtual void                SetBuffer(uint8 type, uint buffer);
    virtual void                SetBufferAtLocation(uint8 type, uint buffer, int location);
    virtual uint                CreateMappedBuffer();
    virtual uint                CreateTexture(int width, int height, uint32 format, byte_t* data);
    virtual void                DestroyTexture(uint texture);
    virtual void                SetTextureAtSlot(uint texture, int slot);
    virtual void                SetImageTextureAtSlot(uint texture, int level, uint8 accessFlags, uint32 format, int slot);
    virtual void                SetTextureAtSpecificLevelAtSlot(uint texture, int level, uint8 format, int slot);
    virtual void                DrawIndexedIndirect(uint bufferForArgs, int drawCount);
    virtual void                PipelineBarrierWait(uint8 barrier);
    virtual void                Flush();
private:
    uint m_vao = 0;
};

CRenderDevice backend;
IRenderDevice* g_renderDevice = &backend;

void CRenderDevice::Init() {
    glCreateVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
}

void CRenderDevice::Shutdown() {
    if(m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}

uint CRenderDevice::CreateRenderTarget() {
    uint fbo = 0;
    glCreateFramebuffers(1, &fbo);
    return fbo;
}

void CRenderDevice::SetRenderTarget(uint target) {
    glBindFramebuffer(GL_FRAMEBUFFER, target);
}

void CRenderDevice::AttachTextureToRenderTarget(uint target, uint texture, uint8 attachPoint) {
    int glAttach = GL_COLOR_ATTACHMENT0;

    switch(attachPoint) {
        case QTAP_COLOR:    glAttach = GL_COLOR_ATTACHMENT0; break;
        case QTAP_DEPTH:    glAttach = GL_DEPTH_ATTACHMENT; break;
        case QTAP_STENCIL:  glAttach = GL_STENCIL_ATTACHMENT; break;
        default: break;
    }

    glNamedFramebufferTexture(target, glAttach, texture, 0);
}

void CRenderDevice::DestroyRenderTarget(uint target) {
    glDeleteFramebuffers(1, &target);
}

void CRenderDevice::SetTextureAtSlot(uint texture, int slot) {
    glBindTextureUnit(slot, texture);
}

void CRenderDevice::SetImageTextureAtSlot(uint texture, int level, uint8 accessFlags, uint32 format, int slot) {
    GLenum glAccess = 0;
    if(accessFlags & QRIA_READ) {
        glAccess = GL_READ_ONLY;
    }

    if(accessFlags & QRIA_WRITE) {
        glAccess = GL_WRITE_ONLY;
    }

    if(accessFlags & QRIA_READ && accessFlags & QRIA_WRITE) {
        glAccess = GL_READ_WRITE;
    }

    GLenum internalFormat = GL_RGBA8;

    switch(format) {
        case QRTF_R32:              internalFormat = GL_R32UI;              break;
        case QRTF_R16:              internalFormat = GL_R16UI;              break;
        case QRTF_R8:               internalFormat = GL_R8;                 break;
        case QRTF_R32G32:           internalFormat = GL_RG32UI;             break;
        case QRTF_R16G16:           internalFormat = GL_RG16UI;             break;
        case QRTF_R8G8:             internalFormat = GL_RG8;                break;
        case QRTF_R32G32B32:        internalFormat = GL_RGB32UI;            break;
        case QRTF_R16G16B16:        internalFormat = GL_RGB16UI;            break;
        case QRTF_R8G8B8:           internalFormat = GL_RGB8;               break;
        case QRTF_R32G32B32A32:     internalFormat = GL_RGBA32UI;           break;
        case QRTF_R16G16B16A16:     internalFormat = GL_RGBA16UI;           break;
        case QRTF_R8G8B8A8:         internalFormat = GL_RGBA8;              break;
    }

    glBindImageTexture(slot, texture, level, GL_FALSE, 0, glAccess, internalFormat);
}

void CRenderDevice::RenderTargetSetColor(float r, float g, float b, float a) {
    // glClearColor(r, g, b, a); DEPRECATED
}

void CRenderDevice::RenderTargetSetColorArray(float* rgba) {
    //DEPRECATED
    // RenderTargetSetColor(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void CRenderDevice::RenderTargetClear(uint target, uint8 bufferTarget, float r, float g, float b) {
    // GLbitfield glFormat = 0;

    // if(targets & RDCT_COLOR) {
    //     glFormat |= GL_COLOR_BUFFER_BIT;
    // }
    // if(targets & RDCT_DEPTH) {
    //     glFormat |= GL_DEPTH_BUFFER_BIT;
    // }
    // if(targets & RDCT_STENCIL) {
    //     glFormat |= GL_STENCIL_BUFFER_BIT;
    // }
    // if(glFormat != 0) glClear(glFormat);
    int attach = GL_COLOR;

    float value[4] = { r, g, b, 1.0f };
    if(bufferTarget & RDCT_COLOR) {
        glClearNamedFramebufferfv(target, GL_COLOR, 0, value);
    }

    if(bufferTarget & RDCT_DEPTH) {
        const float d = 1.0f;
        glClearNamedFramebufferfv(target, GL_DEPTH, 0, &d);
    }
}

uint CRenderDevice::CreateShader(uint8 type, char* sourceCode) {
    int glType;
    switch(type) {
        case QRST_VERTEX: glType = GL_VERTEX_SHADER; break;
        case QRST_FRAGMENT: glType = GL_FRAGMENT_SHADER; break;
        case QRST_COMPUTE: glType = GL_COMPUTE_SHADER; break;
        case QRST_GEOMETRY: glType = GL_GEOMETRY_SHADER; break;
        case QRST_TESSELATOR: glType = GL_TESS_CONTROL_SHADER; break;
    }
    uint shader = glCreateShader(glType);

    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
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

void CRenderDevice::SetShaderPipeline(uint pipeline) {
    glUseProgram(pipeline);
}

void CRenderDevice::DispatchComputePipeline(uint groupsX, uint groupsY, uint groupsZ) {
    glDispatchCompute(groupsX, groupsY, groupsZ);
}

uint CRenderDevice::CreateBuffer(uint8 type, uint8 flags, size_t sizePerElement, int elementCount) {
    uint32 glFlags = 0;
    int glType = 0;
    uint out = 0;

    switch(type) {
        case QRBT_BUFFER: glType = GL_SHADER_STORAGE_BUFFER; break;
        case QRBT_INDIRECT: glType = GL_DRAW_INDIRECT_BUFFER; break;
        case QRBT_INDEX: glType = GL_ELEMENT_ARRAY_BUFFER; break;
    }

    if(flags & QRBF_DYNAMIC) {
        glFlags |= GL_DYNAMIC_STORAGE_BIT;
    }
    if(flags & QRBF_READ) {
        glFlags |= GL_MAP_READ_BIT;
    }
    if(flags & QRBF_WRITE) {
        glFlags |= GL_MAP_WRITE_BIT;
    }
    if(flags & QRBF_PERSISTENT) {
        glFlags |= GL_MAP_PERSISTENT_BIT;
    }
    if(flags & QRBF_COHERENT) {
        glFlags |= GL_MAP_COHERENT_BIT;
    }

    glCreateBuffers(1, &out);
    glNamedBufferStorage(out, sizePerElement * elementCount, nullptr, glFlags);
    return out;
}

void CRenderDevice::PushDataIntoBuffer(uint buffer, size_t sizeOfData, void* data) {
    glNamedBufferSubData(buffer, 0, sizeOfData, data);
}

void CRenderDevice::SetBuffer(uint8 type, uint buffer) {
    int gl = 0;
    switch(type) {
        case QRBT_BUFFER: gl = GL_SHADER_STORAGE_BUFFER; break;
        case QRBT_INDIRECT: gl = GL_DRAW_INDIRECT_BUFFER; break;
        default: break;
    }

    if(type == QRBT_INDEX) {
        glVertexArrayElementBuffer(m_vao, buffer);
    }
    else {
        glBindBuffer(gl, buffer);
    }        
}

void CRenderDevice::SetBufferAtLocation(uint8 type, uint buffer, int location) {
    int gl = 0;
    switch(type) {
        case QRBT_BUFFER: gl = GL_SHADER_STORAGE_BUFFER; break;
        case QRBT_INDIRECT: gl = GL_DRAW_INDIRECT_BUFFER; break;
        default: break;
    }
    glBindBufferBase(gl, location, buffer);
}

uint CRenderDevice::CreateMappedBuffer() {
    return 0;
}

uint CRenderDevice::CreateTexture(int width, int height, uint32 format, byte_t* data) {
    uint tex = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);

    int dataFormat = GL_UNSIGNED_INT;
    int internalFormat = GL_RGBA8;
    int pixelFormat = GL_RED;

    switch(format) {
        case QRTF_R32:              internalFormat = GL_R32UI;      pixelFormat = GL_RED_INTEGER;       dataFormat = GL_UNSIGNED_INT; break;
        case QRTF_R16:              internalFormat = GL_R16UI;      pixelFormat = GL_RED_INTEGER;       dataFormat = GL_UNSIGNED_SHORT; break;
        case QRTF_R32G32:           internalFormat = GL_RG32UI;     pixelFormat = GL_RG_INTEGER;        dataFormat = GL_UNSIGNED_INT; break;
        case QRTF_R16G16:           internalFormat = GL_RG16UI;     pixelFormat = GL_RG_INTEGER;        dataFormat = GL_UNSIGNED_SHORT; break;
        case QRTF_R32G32B32:        internalFormat = GL_RGB32UI;    pixelFormat = GL_RGB_INTEGER;       dataFormat = GL_UNSIGNED_INT; break;
        case QRTF_R16G16B16:        internalFormat = GL_RGB16UI;    pixelFormat = GL_RGB_INTEGER;       dataFormat = GL_UNSIGNED_SHORT; break;
        case QRTF_R32G32B32A32:     internalFormat = GL_RGBA32UI;   pixelFormat = GL_RGBA_INTEGER;      dataFormat = GL_UNSIGNED_INT; break;
        case QRTF_R16G16B16A16:     internalFormat = GL_RGBA16UI;   pixelFormat = GL_RGBA_INTEGER;      dataFormat = GL_UNSIGNED_SHORT; break;
        
        case QRTF_R8:               internalFormat = GL_R8;         pixelFormat = GL_RED;       dataFormat = GL_UNSIGNED_BYTE; break;
        case QRTF_R8G8:             internalFormat = GL_RG8;        pixelFormat = GL_RG;        dataFormat = GL_UNSIGNED_BYTE; break;
        case QRTF_R8G8B8:           internalFormat = GL_RGB8;       pixelFormat = GL_RGB;       dataFormat = GL_UNSIGNED_BYTE; break;
        case QRTF_R8G8B8A8:         internalFormat = GL_RGBA8;      pixelFormat = GL_RGBA;      dataFormat = GL_UNSIGNED_BYTE; break;
    }

    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureStorage2D(tex, 1, internalFormat, width, height); // allocate storage for the texture
    
    if(data) {
        glTextureSubImage2D(tex, 0, 0, 0, width, height, pixelFormat, dataFormat, data);
    }
    return tex;
}

void CRenderDevice::DestroyTexture(uint texture) {
    glDeleteTextures(1, &texture);
}

void CRenderDevice::SetTextureAtSpecificLevelAtSlot(uint texture, int level, uint8 format, int slot) {
    glBindTextureUnit(slot, texture);
}

void CRenderDevice::DrawIndexedIndirect(uint bufferForArgs, int drawCount) {
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, bufferForArgs);
    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, drawCount, 0);
}

void CRenderDevice::PipelineBarrierWait(uint8 barrier) {
    GLbitfield glBarriers = 0;
    if(barrier & QRPB_CMD_BUFFER)       glBarriers |= GL_COMMAND_BARRIER_BIT;
    if(barrier & QRPB_SHADER_STORAGE)   glBarriers |= GL_SHADER_STORAGE_BARRIER_BIT;
    if(barrier & QRPB_TXT_FETCH)        glBarriers |= GL_TEXTURE_FETCH_BARRIER_BIT;
    if(barrier & QRPB_IMG_ACCESS)       glBarriers |= GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;

    glMemoryBarrier(glBarriers);
}

void CRenderDevice::Flush() {
    glFlush();
}