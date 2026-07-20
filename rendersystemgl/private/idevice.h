#pragma once
#include <appframework/appframework.h>
#include <types.h>

enum clearTarget_t : uint32 {
    RDCT_COLOR              = 1 << 0,
    RDCT_DEPTH              = 1 << 1,
    RDCT_STENCIL            = 1 << 2
};

class CGPUBuffer;

typedef  struct {
    uint    count;
    uint    instanceCount;
    uint    firstIndex;
    int     baseVertex;
    uint    baseInstance;
} indirectCommand_t;

//Backend class for doing OpenGL commands.
stripped_vclass IRenderDevice {
public:
    virtual void                Init() = 0;
    virtual void                Shutdown() = 0;

    virtual void                TargetSetColor(float r, float g, float b, float a) = 0;
    virtual void                TargetSetColorArray(float* rgba) = 0;

    virtual void                TargetsClear(uint32 target) = 0;

    virtual uint                CreateBuffer() = 0;

    virtual uint                CreateTexture() = 0;
    virtual void                SetTexture() = 0;
    virtual void                EnableTextureSlot(int slotId) = 0;

    virtual void                FlushDevice() = 0;

    virtual void                DrawIndexedInstancedIndirect(CGPUBuffer* bufferForArgs, uint byteOffsetPerBuffer) = 0;
};