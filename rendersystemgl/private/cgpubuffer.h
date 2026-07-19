#pragma once
#include <types.h>

enum gpuBufferType_t : uint8 {
    QGPU_BUFFER_GPU_STORAGE
};

enum gpuBufferFlag : uint8 {
    QGPU_BUFFER_PERSISTENT,
    QGPU_BUFFER_COHERENT
};

class CGPUBuffer {
public:
    void                Init(const char* name, int elementCount);

    void                PushBackData();

    void                BindBuffer(uint8 type, int location);
    void                FreeBinding();
private:
    int                 m_currentAllocationSize;
    int                 m_sizePerElement;

    const char*         m_name;
};