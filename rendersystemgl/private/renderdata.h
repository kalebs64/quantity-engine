#pragma once
#include <tier0.h>
#include <types.h>

struct plane_t {
    float x, y, z, w;
};

struct frustumData_t {
    plane_t     m_planes[6];
    float       m_cameraPosition[3];
    float       m_padding;
};

typedef struct materialData_s {
    uint64      m_albedoTexHandle;
    uint64      m_normalTexHandle;
    float       m_baseColorTint[4];
} materialData_t;

typedef struct instanceData_s {
    Matrix4f    m_worldMatrix;
    uint32      m_sliceID;
    uint32      m_materialID;
    uint 		padding0;
    uint 		padding1;
} instanceData_t;