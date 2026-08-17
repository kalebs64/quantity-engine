#include "cgpubuffer.h"
#include "idevice.h"
#include "enums.h"
#include <string>
#include <string.h>

CGPUBuffer::CGPUBuffer() {
    m_allocatedName = false;
    m_positionInBuffer = 0;
    m_sizePerElement = 0;
    m_bindLocation = 0;
    m_buffer = -1;
    m_name = "undefined";
}

CGPUBuffer::~CGPUBuffer() {
    if(m_allocatedName) {
        delete[] m_name;
    }
}

void CGPUBuffer::Init(const char* pName, int pGPULocation, int pSizeOfElement, uint8 flags, int pInitialCount) {
    m_sizePerElement = pSizeOfElement;
    m_bindLocation = pGPULocation;

    g_renderDevice->CreateBuffer(QRBT_BUFFER, flags, m_sizePerElement, pInitialCount);

    if(!pName || !pName[0]) {
        std::string generatedName = "gpu_buffer_";
        int nameUUID = pGPULocation + pSizeOfElement + pInitialCount;

        generatedName += std::to_string(nameUUID);

        char* copy = new char[generatedName.length() + 1];
        std::strcpy(copy, generatedName.c_str());

        m_name = copy;
        m_allocatedName = true;
    }
    else {
        m_name = pName;
        m_allocatedName = false;
    }
}

void CGPUBuffer::WriteBufferDataTail(void* pData, int pWriteSize) {
    if(pData) {
        g_renderDevice->SetBufferData(m_buffer, m_positionInBuffer, pWriteSize, pData);
        m_positionInBuffer += pWriteSize;
    }
}

void CGPUBuffer::OverwriteBufferData(void* pData, int pWriteSize) {
    if(pData) {
        g_renderDevice->SetBufferData(m_buffer, 0, pWriteSize, pData);
        m_positionInBuffer = pWriteSize; // we overwrote so we need to reset the new buffer ending
    }
}

void CGPUBuffer::SetBuffer(int pLocation) {
    if(pLocation < 0) {
        g_renderDevice->SetBufferAtLocation(QRBT_BUFFER, m_buffer, m_bindLocation);
    }
    else {
        g_renderDevice->SetBufferAtLocation(QRBT_BUFFER, m_buffer, pLocation);
    }
}

void CGPUBuffer::FreeBinding() {}