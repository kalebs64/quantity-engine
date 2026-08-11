#include "itexture.h"
#include "ctexture.h"
#include <unordered_map>
#include <string>

class CTextureManager : public ITextureManager {
public:
    virtual void                        Init();
    virtual void                        Shutdown();
    virtual const char*                 ListContents();
    virtual ITexture*                   LoadImage(const byte_t* pImageBytes, int pWidth, int pHeight, imageFormat_t pFormat, bool pBindless);
    virtual ITexture*                   GetImage(const char* name) const;
private:
    std::unordered_map<std::string, ITexture*>     m_textures;
};

CTextureManager man;
ITextureManager* g_textureManager = &man;

void CTextureManager::Init() {

}

void CTextureManager::Shutdown() {

}

const char* CTextureManager::ListContents() {
    return nullptr;
}

ITexture* CTextureManager::LoadImage(const byte_t* pImageBytes, int pWidth, int pHeight, imageFormat_t pFormat, bool pBindless) {
    CTexture* txt = new CTexture();

    if(txt && pImageBytes) {
        if(txt->LoadFromRawBytes2D(pImageBytes, pWidth, pHeight, pFormat, pBindless)) {
            std::string name = txt->Name();
            m_textures[name] = txt;
            return m_textures[name];
        }
    }
    return nullptr;
}

ITexture* CTextureManager::GetImage(const char* name) const {
    return nullptr;
}
