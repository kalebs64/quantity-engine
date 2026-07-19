#pragma once
#include "itexture.h"
#include <ifilesystem.h>

class CTexture : public ITexture {
public:
                                CTexture();

    void                        Bind();
    bool                        LoadFromRawBytes2D(const byte_t* picBytes, int w, int h, imageFormat_t format, materialInputType_t inputSlot);
    void                        PurgeImage();

    void                        SetIsDependency(bool value);
    bool                        IsLoaded() {return !m_purged;}
    bool                        IsDependency() {return m_isDependency;}

    std::string                 Name() const {return m_name;}
    void                        SetName(std::string newName);

    uint                        GLHandle() {return m_glHandle;}
    materialInputType_t         GetInputSlot() {return m_inputType;}
private:
    imageType_t                 m_type;
    materialInputType_t         m_inputType;

    int                         m_width;
    int                         m_height;

    bool                        m_isDependency;
    bool                        m_purged;

    std::string                 m_name;

    uint                        m_glHandle;

    byte_t*                     m_data;
};

class CTextureSystem : public ITextureSystem {
public:
    virtual void                        Init();
    virtual void                        Shutdown();

    //Loads only .bit images into memory
    virtual ITexture*                   LoadImage(const char* path, imageType_t type, imageFormat_t format, materialInputType_t inputSlot);
    virtual ITexture*                   GetImage(const char* name) const;

    virtual void                        ReloadLoaded();
};

CTextureSystem texman;
ITextureSystem* g_textureSystem = &texman;

void CTextureSystem::Init() {
    g_fileSystem->RegisterPathAlias("directory_texture", "art/materials");
}

void CTextureSystem::Shutdown() {}

ITexture* CTextureSystem::LoadImage(const char* path, imageType_t type, imageFormat_t format, materialInputType_t inputSlot) {}

ITexture* CTextureSystem::GetImage(const char* name) const {}

void CTextureSystem::ReloadLoaded() {}