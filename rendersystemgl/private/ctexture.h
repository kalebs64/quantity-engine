#pragma once
#include "itexture.h"
#include <types.h>
#include <tier0.h>

class CTexture : public ITexture {
public:
                                CTexture();

    bool                        LoadFromRawBytes2D(const byte_t* pImageBytes, int pWidth, int pHeight, imageFormat_t pFormat, bool pBindless);
    void                        PurgeImage();

    bool                        IsLoaded() {return !m_purged;}

    const char*                 Name() const {return m_name;}
    void                        SetName(const char* pName);

    Uint2                       GetBindless() const {return m_bindlessHandle;}
private:
    imageType_t                 m_type;

    int                         m_width;
    int                         m_height;

    bool                        m_purged;

    const char*                 m_name;

    uint                        m_handle;
    Uint2                       m_bindlessHandle;
};