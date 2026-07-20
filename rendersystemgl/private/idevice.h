#pragma once
#include <appframework/appframework.h>
#include <types.h>

enum clearTarget_t : uint32 {
    RDCT_COLOR              = 1 << 0,
    RDCT_DEPTH              = 1 << 1,
    RDCT_STENCIL            = 1 << 2
};

enum shaderType_t : uint8 {
    QRST_VERTEX = 0,
    QRST_FRAGMENT,
    QRST_COMPUTE,
    QRST_GEOMETRY,
    QRST_TESSELATOR,
    QRST_TYPE_MAX
};

enum bufferType_t : uint8 {
    QRBT_BUFFER,
    QRBT_INDIRECT,
    QRBT_SHADER_MAX
};

enum bufferFlag_t : uint8 {
    QRBF_DYNAMIC            = 1 << 0,
    QRBF_READ               = 1 << 1,
    QRBF_WRITE              = 1 << 2,
    QRBF_PERSISTENT         = 1 << 3,
    QRBF_COHERENT           = 1 << 4
};

typedef struct {
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

    //set clear color
    virtual void                TargetSetColor(float r, float g, float b, float a) = 0;
    //set clear color
    virtual void                TargetSetColorArray(float* rgba) = 0;

    //Clear color, depth, or stenctil
    virtual void                TargetsClear(uint32 targets) = 0;

    //create a shader of specified type with provided code
    virtual uint                CreateShader(uint8 type, char* sourceCode) = 0;
    //give all compiled shader and it will return a program using them.
    virtual uint                CreateShaderPipeline(uint* shaders) = 0;
    //set the current shader
    virtual void                SetShaderPipeline(uint pipeline) = 0;

    //create a given type of buffer with specified flags.
    virtual uint                CreateBuffer(uint8 type, uint8 flags) = 0;
    //create a mapped buffer.
    virtual uint                CreateMappedBuffer() = 0;

    // virtual uint                CreateTexture(byte_t* data) = 0;
    // virtual void                DestroyTexture() = 0;
    // virtual void                EnableTextureSlot(int slotId) = 0;
    // virtual void                SetTexture() = 0;

    //indirect rendering command.
    virtual void                DrawIndexedInstancedIndirect(uint bufferForArgs) = 0;

    //force the execution of all GL commands now.
    virtual void                Flush() = 0;
};