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

struct ALIGN16 materialData_t {
    Uint2      m_albedoGPU;
    float      m_padding;
    float      m_albedoFactor[4];
    float      m_roughnessFactor;
    float      m_metallicFactor;
};

typedef struct instanceData_s {
    Matrix4x4   m_worldMatrix;
    uint32      m_sliceID;
    uint32      m_materialID;
    uint        m_padding0;
    uint        m_padding1;
} instanceData_t;

struct frameConstants_t {
    Matrix4x4   m_viewProj;
    uint        m_frameInstanceCount;
    float       m_padding[3];
};