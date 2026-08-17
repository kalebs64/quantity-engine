#pragma once
#include <tier0.h>
#include <types.h>
#include <string>

class ITexture;

class IMaterial {
public:
    virtual void                SetAlbedoByPointer(ITexture* texture) = 0;
    virtual void                SetAlbedoByName(const char* name) = 0;

    virtual const char*         GetName() const = 0;
    virtual uint                GetId() const = 0;
};

class ITexture;

stripped_vclass IMaterialManager {
public:
    virtual void                Init() = 0;
    virtual void                Shutdown() = 0;

    virtual IMaterial*          CreateMaterial(const char* name) = 0;

    virtual bool                NeedsReload() = 0;
    virtual void                Reload() = 0;

    virtual void                SetBufferToSlot(int pSlot = 0) = 0;
};

#define QUANTITY_MATERIAL_MANAGER "QUANTITY_MATERIALMANAGER_001"
extern IMaterialManager* g_materialManager;