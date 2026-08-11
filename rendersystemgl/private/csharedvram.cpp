#pragma once
#include "idevice.h"
#include "isharedvram.h"
#include "cgpubuffer.h"
#include "enums.h"
#include "imesh.h"
#include "renderdata.h"

#define QUANTITY_VERTEX_ALLOCATION      2048*2048
#define QUANTITY_INDEXES_ALLOCATION     2048*2048
#define QUANTITY_INSTANCES_ALLOCATION   1024
#define QUANTITY_SLICES_ALLOCATION      (2048*2048)/2
#define QUANTITY_VIEW_ALLOCATION        1
#define QUANTITY_CMD_ALLOCATION         2048

class CSharedVRAM : public ISharedVRAM {
public:
    virtual void            Init();
    virtual void            OverwriteRegionOfBuffer(int pBufferId, void* pData, int pSizeOfData);
    virtual void            WriteToBufferTail(int pBufferId, void* pData, int pSizeOfData);
    virtual void            SetBuffer(int pBufferId);
    virtual void            ClearBuffer(int pBufferId);
private:
    CGPUBuffer              m_buffers[QSVB_COUNT];
};

CSharedVRAM csv;
ISharedVRAM* g_sharedVRAM = &csv;

void CSharedVRAM::Init() {
    m_buffers[QSVB_VERTEX].Init   ("vertex_buffer",         QSVB_VERTEX,    sizeof(vertex_t),           QRBF_DYNAMIC | QRBF_READ, QUANTITY_VERTEX_ALLOCATION);
    m_buffers[QSVB_INDEXES].Init  ("index_buffer",          QSVB_INDEXES,   sizeof(uint),               QRBF_DYNAMIC | QRBF_READ, QUANTITY_INDEXES_ALLOCATION);
    m_buffers[QSVB_INSTANCE].Init ("instance_buffer",       QSVB_INSTANCE,  sizeof(instanceData_t),     QRBF_DYNAMIC | QRBF_READ, QUANTITY_INSTANCES_ALLOCATION);
    m_buffers[QSVB_SLICES].Init   ("slice_buffer",          QSVB_SLICES,    sizeof(poolSliceData_t),    QRBF_DYNAMIC | QRBF_READ, QUANTITY_SLICES_ALLOCATION);
    m_buffers[QSVB_CAMERA].Init   ("view_buffer",           QSVB_CAMERA,    sizeof(frameConstants_t),   QRBF_DYNAMIC | QRBF_READ, QUANTITY_VIEW_ALLOCATION);
    m_buffers[QSVB_COMMAND].Init  ("command_buffer",        QSVB_COMMAND,   sizeof(drawIndirect_t),     QRBF_DYNAMIC | QRBF_READ, QUANTITY_CMD_ALLOCATION);
}

void CSharedVRAM::OverwriteRegionOfBuffer(int pBufferId, void* pData, int pSizeOfData) {
    m_buffers[pBufferId].OverwriteBufferData(pData, pSizeOfData);
}

void CSharedVRAM::WriteToBufferTail(int pBufferId, void* pData, int pSizeOfData) {
    m_buffers[pBufferId].WriteBufferDataTail(pData, pSizeOfData);
}

void CSharedVRAM::SetBuffer(int pBufferId) {
    m_buffers[pBufferId].SetBuffer();
}

void CSharedVRAM::ClearBuffer(int pBufferId) {
}