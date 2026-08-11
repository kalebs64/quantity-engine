#pragma once
#include <types.h>

enum clearTarget_t : uint8 {
    RDCT_COLOR              = 1 << 0,
    RDCT_DEPTH              = 1 << 1,
    RDCT_STENCIL            = 1 << 2
};

enum depthFunc_t : uint8 {
    RDFN_LESS              = 1 << 0
};

enum textureFormat_t : uint32 {
    //color
    QRTF_R32                = 0,
    QRTF_R16,
    QRTF_R8,
    QRTF_R32G32,
    QRTF_R16G16,
    QRTF_R8G8,
    QRTF_R32G32B32,
    QRTF_R16G16B16,
    QRTF_R8G8B8,
    QRTF_R32G32B32A32,
    QRTF_R16G16B16A16,
    QRTF_R8G8B8A8,
    //depth
    QRTF_D32,
    QRTF_D24,
    QRTF_D16,
    QRTF_FORMAT_MAX
};


enum targetAttachPoint_t : uint8 {
    QTAP_COLOR = 0,
    QTAP_DEPTH,
    QTAP_STENCIL
};

enum shaderType_t : uint8 {
    QRST_VERTEX = 0,
    QRST_FRAGMENT,
    QRST_COMPUTE,
    QRST_GEOMETRY,
    QRST_TESSELATOR,
    QRST_TYPE_MAX
};

enum bufferType_t : uint8 {
    QRBT_BUFFER,
    QRBT_INDIRECT,
    QRBT_INDEX,
    QRBT_SHADER_MAX
};

enum bufferFlag_t : uint8 {
    QRBF_DYNAMIC            = 1 << 0,
    QRBF_READ               = 1 << 1,
    QRBF_WRITE              = 1 << 2,
    QRBF_PERSISTENT         = 1 << 3,
    QRBF_COHERENT           = 1 << 4
};

enum imageAccess_t : uint8 {
    QRIA_READ               = 1 << 1,
    QRIA_WRITE              = 1 << 2
};

enum pipeBarrier_t : uint8 {
    QRPB_CMD_BUFFER         = 1 << 0,
    QRPB_SHADER_STORAGE     = 1 << 1,
    QRPB_TXT_FETCH          = 1 << 2,
    QRPB_IMG_ACCESS         = 1 << 3
};