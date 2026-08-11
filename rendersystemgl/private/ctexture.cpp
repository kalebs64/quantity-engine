#pragma once
#include "ctexture.h"
#include "enums.h"
#include "idevice.h"

CTexture::CTexture() {
    m_width = 0;
    m_height = 0;
    m_purged = true;
    m_handle = -1;
    m_bindlessHandle = Uint2(0);
    m_name = "undefined";
}

bool CTexture::LoadFromRawBytes2D(const byte_t* pImageBytes, int pWidth, int pHeight, imageFormat_t pFormat, bool pBindless) {
    uint32 format;

    m_width = pWidth;
    m_height = pHeight;

    switch(pFormat) {
        case IT_RGBA32F: format = QRTF_R32G32B32A32; break;
        case IT_RGBA16F: format = QRTF_R16G16B16A16; break;
        case IT_RGBA8F: format =  QRTF_R8G8B8A8; break;
        default: break;
    }

    m_handle = g_renderDevice->CreateTexture(m_width, m_height, format, pImageBytes);
    if(m_handle && pBindless) {
        m_bindlessHandle = g_renderDevice->MarkTextureBindless(m_handle);
        m_purged = false;

        int uuid = m_width + m_height + m_handle + (int)m_purged + m_bindlessHandle.x + m_bindlessHandle.y;
        std::string generatedName = "itexture_";

        generatedName += std::to_string(uuid);

        char* copy = new char[generatedName.length() + 1];
        std::strcpy(copy, generatedName.c_str());

        m_name = copy;
        return true;
    }
    return false;
}

void CTexture::PurgeImage() {

}

void CTexture::SetName(const char* pName) {
    m_name = pName;
}