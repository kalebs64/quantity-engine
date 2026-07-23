#pragma once
#include <appframework/appframework.h>
#include <types.h>

enum clearTarget_t : uint8 {
    RDCT_COLOR              = 1 << 0,
    RDCT_DEPTH              = 1 << 1,
    RDCT_STENCIL            = 1 << 2
};

enum textureFormat_t : uint32 {
    //color
    QRTF_R32                = 0,
    QRTF_R16,
    QRTF_R8,
    QRTF_R32G32,
    QRTF_R16G16,
    QRTF_R8G8,
    QRTF_R32G32B32,
    QRTF_R16G16B16,
    QRTF_R8G8B8,
    QRTF_R32G32B32A32,
    QRTF_R16G16B16A16,
    QRTF_R8G8B8A8,
    //depth
    QRTF_D32,
    QRTF_D24,
    QRTF_D16,
    QRTF_FORMAT_MAX
};


enum targetAttachPoint_t : uint8 {
    QTAP_COLOR = 0,
    QTAP_DEPTH,
    QTAP_STENCIL
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
    QRBT_INDEX,
    QRBT_SHADER_MAX
};

enum bufferFlag_t : uint8 {
    QRBF_DYNAMIC            = 1 << 0,
    QRBF_READ               = 1 << 1,
    QRBF_WRITE              = 1 << 2,
    QRBF_PERSISTENT         = 1 << 3,
    QRBF_COHERENT           = 1 << 4
};

enum imageAccess_t : uint8 {
    QRIA_READ               = 1 << 1,
    QRIA_WRITE              = 1 << 2
};

enum pipeBarrier_t : uint8 {
    QRPB_CMD_BUFFER         = 1 << 0,
    QRPB_SHADER_STORAGE     = 1 << 1,
    QRPB_TXT_FETCH          = 1 << 2,
    QRPB_IMG_ACCESS         = 1 << 3
};

struct drawIndirect_t {
    uint count;
    uint instanceCount;
    uint first;
    uint baseInstance;
};

//Backend class for doing OpenGL commands.
stripped_vclass IRenderDevice {
public:
    virtual void                Init() = 0;
    virtual void                Shutdown() = 0;

    //create a render target
    virtual uint                CreateRenderTarget() = 0;
    //set target as the current render target to render to
    virtual void                SetRenderTarget(uint target) = 0;
    //attach a 2d texture to a specific point of a render target
    virtual void                AttachTextureToRenderTarget(uint target, uint texture, uint8 attachPoint) = 0;
    // virtual void                BlitTextureToRenderTarget(uint target, uint texture, uint8 attachPoint) = 0;
    //delete this target
    virtual void                DestroyRenderTarget(uint target) = 0;

    //set clear color (a render target doesn't need to be set for this)
    virtual void                RenderTargetSetColor(float r, float g, float b, float a) = 0;
    //set clear color (a render target doesn't need to be set for this)
    virtual void                RenderTargetSetColorArray(float* rgba) = 0;

    //Clear color, depth, or stenctil (a render target doesn't need to be set for this)
    virtual void                RenderTargetClear(uint target, uint8 bufferTarget, float r, float g, float b) = 0;

    //create a shader of specified type with provided code
    virtual uint                CreateShader(uint8 type, char* sourceCode) = 0;
    //give all compiled shader and it will return a program using them.
    virtual uint                CreateShaderPipeline(uint* shaders, int count) = 0;
    //set the current shader
    virtual void                SetShaderPipeline(uint pipeline) = 0;
    virtual void                DispatchComputePipeline(uint groupsX, uint groupsY, uint groupsZ) = 0;

    //create a given type of buffer with specified flags.
    virtual uint                CreateBuffer(uint8 type, uint8 flags, size_t sizePerElement, int elementCount) = 0;
    virtual void                PushDataIntoBuffer(uint buffer, size_t sizeOfData, void* data) = 0;
    virtual void                SetBuffer(uint8 type, uint buffer) = 0;
    virtual void                SetBufferAtLocation(uint8 type, uint buffer, int location) = 0;
    //create a mapped buffer.
    virtual uint                CreateMappedBuffer() = 0;

    virtual uint                CreateTexture(int width, int height, uint32 format, byte_t* data) = 0;
    virtual void                DestroyTexture(uint texture) = 0;
    //probably want to use bindless textures will remake with that in mind
    virtual void                SetTextureAtSlot(uint texture, int slot) = 0;
    virtual void                SetImageTextureAtSlot(uint texture, int level, uint8 accessFlags, uint32 format, int slot) = 0;
    virtual void                SetTextureAtSpecificLevelAtSlot(uint texture, int level, uint8 format, int slot) = 0;

    //indirect rendering command.
    virtual void                DrawIndexedIndirect(uint bufferForArgs, int drawCount) = 0;

    virtual void                PipelineBarrierWait(uint8 barrier) = 0;
    //force the execution of all GL commands now.
    virtual void                Flush() = 0;
};

extern IRenderDevice* g_renderDevice;
//no need for a version string, this is strictly an internal interface.