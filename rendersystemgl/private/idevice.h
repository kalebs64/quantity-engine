#pragma once
#include <appframework/appframework.h>
#include <types.h>
#include <tier0.h>

struct drawIndirect_t {
    uint count;
    uint instanceCount;
    uint firstIndex;
    uint baseVertex;
    uint baseInstance;
};

struct indirectDispatch_t {
    uint m_groupCountX;
    uint m_groupCountY;
    uint m_groupCountZ;
    uint m_pixelCount;
    uint m_pixelBufferOffset;
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
    virtual void                SetDispatchBuffer(uint pDispatchBuffer) = 0;
    virtual void                DispatchComputePipelineIndirect(int pOffset) = 0;

    //create a given type of buffer with specified flags.
    virtual uint                CreateBuffer(uint8 type, uint8 flags, size_t sizePerElement, int elementCount) = 0;
    [[deprecated("Use SetBufferData instead.")]]
    virtual void                PushDataIntoBuffer(uint buffer, size_t sizeOfData, void* data) = 0;
    virtual void                GetBufferData(uint pBuffer, size_t pBufferOffset, size_t pBufferSize, void* pOutData) = 0;
    virtual void                SetBufferData(uint buffer, int offset, size_t sizeOfData, void* data) = 0;
    virtual void                SetBuffer(uint8 type, uint buffer) = 0;
    virtual void                SetBufferAtLocation(uint8 type, uint buffer, int location) = 0;
    //create a mapped buffer.
    virtual uint                CreateMappedBuffer() = 0;

    virtual uint                CreateTexture(int width, int height, uint32 format, const byte_t* data) = 0;
    virtual Vector2             PackTexture2Uint32(uint64 handle) = 0;
    virtual Vector2             MarkTextureBindless(uint texture) = 0;
    virtual void                DestroyTexture(uint texture) = 0;
    //probably want to use bindless textures will remake with that in mind
    virtual void                SetTextureAtSlot(uint texture, int slot) = 0;
    virtual void                SetImageTextureAtSlot(uint texture, int level, uint8 accessFlags, uint32 format, int slot) = 0;
    virtual void                SetTextureAtSpecificLevelAtSlot(uint texture, int level, uint8 format, int slot) = 0;
    virtual void                BlitTextureToScreen(uint texture, int width, int height) = 0;

    virtual void                EnableDepthTesting(bool pEnabled) = 0;
    virtual void                EnableDepthWriting(bool pEnabled) = 0;
    virtual void                SetDepthFunc(uint8 func) = 0;
    //indirect rendering command.
    virtual void                DrawIndexedIndirect(uint bufferForArgs, int drawCount) = 0;

    virtual void                PipelineBarrierWait(uint8 barrier) = 0;
    //force the execution of all GL commands now.
    virtual void                Flush() = 0;
};

extern IRenderDevice* g_renderDevice;
//no need for a version string, this is strictly an internal interface.