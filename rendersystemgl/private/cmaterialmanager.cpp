#include "imaterialmanager.h"
#include "ctexture.h"
#include "enums.h"
#include "renderdata.h"
#include "cgpubuffer.h"
#include <vector>
#include <string>
#include <unordered_map>

class CMaterial : public IMaterial {
public:
    virtual void                SetAlbedoByPointer(ITexture* texture);
    virtual void                SetAlbedoByName(const char* name);
    virtual const char*         GetName() const;
    virtual uint                GetId() const;

    materialData_t*             ForkOverData() const;
private:
    materialData_t              m_data;

    const char*                 m_name;
};

void CMaterial::SetAlbedoByPointer(ITexture* texture) {
    CTexture* t = static_cast<CTexture*>(texture);
    m_data.m_albedoGPU = t->GetBindless();
}

void CMaterial::SetAlbedoByName(const char* name) {
    CTexture* t = static_cast<CTexture*>(g_textureManager->GetImage(name));
}

const char* CMaterial::GetName() const {
    return m_name;
}

uint CMaterial::GetId() const {
    return 0;
}

materialData_t* CMaterial::ForkOverData() const {
    return nullptr;
}

class CMaterialManager : public IMaterialManager {
public:
    virtual void                Init();
    virtual void                Shutdown();
    virtual IMaterial*          CreateMaterial(const char* name);
    virtual bool                NeedsReload();
    virtual void                Reload();
    virtual void                SetBufferToSlot(int pSlot);
private:
    bool                        m_materialsReloaded;

    CGPUBuffer                  m_materialsGPU;
    std::vector<materialData_t> m_materialsCPU;
};

CMaterialManager man;
IMaterialManager* g_materialManager = &man;

void CMaterialManager::Init() {
    m_materialsCPU = std::vector<materialData_t>(MAX_MATERIALS);
    for(int i = 0; i < MAX_MATERIALS; ++i) {
        m_materialsCPU[i].m_albedoGPU = Uint2(0.0f);
    }

    std::string n = "material_buffer"+std::to_string(MAX_MATERIALS);
    m_materialsGPU.Init(n.c_str(), 5, sizeof(materialData_t), QRBF_DYNAMIC | QRBF_READ, MAX_MATERIALS);

    m_materialsReloaded = true;
}

void CMaterialManager::Shutdown() {
}

IMaterial* CMaterialManager::CreateMaterial(const char* name) {
    
}

bool CMaterialManager::NeedsReload() {
    return m_materialsReloaded;
}

void CMaterialManager::Reload() {}

void CMaterialManager::SetBufferToSlot(int pSlot) {
    m_materialsGPU.SetBuffer(pSlot);
}