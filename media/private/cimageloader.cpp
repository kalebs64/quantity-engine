#include "iimageloader.h"
#include "image_stb.h"

class CImageLoader : public IImageLoader {
public:
    virtual void                FlipImagesOnLoad(bool value);
    virtual bool                LoadImage(quantityImage_t* img);
    virtual void                FreeImage(quantityImage_t* img);
};

CImageLoader imgl;
extern IImageLoader* g_imageLoader = &imgl;

void CImageLoader::FlipImagesOnLoad(bool value) {
    stbi_set_flip_vertically_on_load(value);
}

bool CImageLoader::LoadImage(quantityImage_t* img) {
    img->m_data = stbi_load(img->m_name, &img->m_width, &img->m_height, &img->m_channelCount, 0);

    if(img->m_data) {
        img->m_hasContents = true;
        return true;
    }

    return false;
}

void CImageLoader::FreeImage(quantityImage_t* img) {
    if(img->m_data) {
        stbi_image_free(img->m_data);
    }
}