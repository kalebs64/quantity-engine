#pragma once
#include <types.h>
#include <string>

struct bimgHeader_t {
    char    magic[4]; // BIMG
    int     version;
    int     imageType;
    int     materialInputType;
    int     width;
    int     height;
    int     depth;
    int     mipCount;
    int     format;
    bool    useMips;
    bool    usingFTT;
};

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
    virtual void                        Bind() = 0;
    virtual bool                        LoadFromRawBytes2D(const byte_t* picBytes, int w, int h, imageFormat_t format, materialInputType_t inputSlot) = 0;
    virtual void                        PurgeImage() = 0;

    virtual void                        SetIsDependency(bool value) = 0;
    virtual bool                        IsLoaded() = 0;
    virtual bool                        IsDependency() = 0;

    virtual std::string                 Name() const = 0;
    virtual void                        SetName(std::string newName) = 0;

    virtual uint                        GLHandle() = 0;
    virtual materialInputType_t         GetInputSlot() = 0;
};

class ITextureSystem {
public:
    virtual void                        Init() = 0;
    virtual void                        Shutdown() = 0;

    //Loads only .bit images into memory
    virtual ITexture*                   LoadImage(const char* path, imageType_t type, imageFormat_t format, materialInputType_t inputSlot) = 0;
    virtual ITexture*                   GetImage(const char* name) const = 0;

    virtual void                        ReloadLoaded() = 0;
};

extern ITextureSystem* g_textureSystem;