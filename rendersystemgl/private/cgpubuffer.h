#pragma once
#include <types.h>

class CGPUBuffer {
public:
                        CGPUBuffer();
                        ~CGPUBuffer();

    void                Init(const char* pName, int pGPULocation, int pSizeOfElement, uint8 flags, int pInitialCount);

    void                WriteBufferDataTail(void* pData, int pWriteSize);
    void                OverwriteBufferData(void* pData, int pWriteSize);

    void                SetBuffer();
    void                FreeBinding();
private:
    bool                m_allocatedName;
    int                 m_positionInBuffer;
    int                 m_sizePerElement;
    int                 m_bindLocation;

    uint                m_buffer;

    const char*         m_name;
};