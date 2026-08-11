#pragma once
#include <types.h>

enum bufferId_t : int {
    QSVB_VERTEX = 0,
    QSVB_INDEXES,
    QSVB_INSTANCE,
    QSVB_SLICES,
    QSVB_CAMERA,
    QSVB_PARTICLE,
    QSVB_COMMAND,
    QSVB_COUNT
};

class ISharedVRAM {
public:
    virtual void            Init() = 0;
    virtual void            OverwriteRegionOfBuffer(int pBufferId, void* pData, int pSizeOfData) = 0;
    virtual void            WriteToBufferTail(int pBufferId, void* pData, int pSizeOfData) = 0;
    virtual void            SetBuffer(int pBufferId) = 0;
    virtual void            ClearBuffer(int pBufferId) = 0;
};

extern ISharedVRAM* g_sharedVRAM;