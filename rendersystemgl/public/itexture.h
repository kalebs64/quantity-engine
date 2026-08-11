#pragma once
#include <types.h>
#include <string>

enum imageType_t : uint32 {
    IT_2D = 0,
    IT_3D
};

enum imageFormat_t : uint32 {
    IT_NONE           = 0,
    IT_RGBA32F,
    IT_RGBA16F,
    IT_RGBA8F,
    IT_NEXT_VALUE
};

enum materialInputType_t : uint32 {
    IMI_ALBEDO,
    IMI_SPECULAR,
    IMI_NORMAL,
    IMI_COUNT
};

enum imageFilter_t : uint32 {
    IMF_LINEAR_MIPMAP_NEAREST,
    IMF_LINEAR_MIPMAP_LINEAR,
    IMF_NEAREST,
    IMF_LINEAR,
    IMF_NEAREST_MIPMAP_NEAREST,
    IMF_NEAREST_MIPMAP_LINEAR
};

class ITexture {
public:
    virtual bool                        LoadFromRawBytes2D(const byte_t* pImageBytes, int pWidth, int pHeight, imageFormat_t pFormat, bool pBindless) = 0;
    virtual void                        PurgeImage() = 0;

    virtual bool                        IsLoaded() = 0;

    virtual const char*                 Name() const = 0;
    virtual void                        SetName(const char* newName) = 0;
};

class ITextureManager {
public:
    virtual void                        Init() = 0;
    virtual void                        Shutdown() = 0;
    
    virtual const char*                 ListContents() = 0;

    virtual ITexture*                   LoadImage(const byte_t* pImageBytes, int pWidth, int pHeight, imageFormat_t pFormat, bool pBindless) = 0;
    virtual ITexture*                   GetImage(const char* name) const = 0;
};

#define QUANTITY_TEXTUREMANAGER_VERSION "QUANTITY_TXTRMAN_001"
extern ITextureManager* g_textureManager;