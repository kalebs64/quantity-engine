#pragma once
#include <tier0.h>
#include <string>

class IMaterial {
public:
    virtual void                SetAlbedoFactor(Vector3 value) = 0;
};

class ITexture;

stripped_vclass IMaterialSystem {
public:
    virtual void                Init() = 0;
    virtual void                Shutdown() = 0;

    virtual ITexture*           CreateTexture(const char* name) = 0;
    virtual IMaterial*          CreateMaterial(const char* name) = 0;

    virtual bool                NeedsReload() = 0;
    virtual void                Reload() = 0;

    //with pAppend we will only add new data to the end of the GPU buffer, without we replace the entire buffer.
    virtual void                SubmitToSharedVRAM(bool pAppend = false) = 0;
};

#define QUANTITY_SHADERSYSTEM_VERSION "QUANTITY_MATERIALSYSTEM_001"
extern IMaterialSystem* g_materialSystem;