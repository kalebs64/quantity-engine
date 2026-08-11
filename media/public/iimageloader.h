#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <types.h>

struct quantityImage_t {
    int                         m_width;
    int                         m_height;
    int                         m_channelCount;
    bool                        m_hasContents;
    const char*                 m_name;
    byte_t*                     m_data;
};

class IImageLoader {
public:
    virtual void                FlipImagesOnLoad(bool value) = 0;

    virtual bool                LoadImage(quantityImage_t* img) = 0;
    virtual void                FreeImage(quantityImage_t* img) = 0;
};

#define QUANTITY_IMAGELOADER_VERSION "QUANTITY_IMAGE_LOADER_001"
extern IImageLoader* g_imageLoader;