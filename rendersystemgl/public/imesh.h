#pragma once
#include <types.h>

struct vertex_t {
    float pos[3];
    float normal[3];
    float uv[2];
};

typedef struct poolSliceData_s {
    uint32                      vertexCacheOffset;
    uint32                      indexCacheOffset;
    uint32                      indexCount;
} poolSliceData_t;

struct mesh_t {
    float                   minBounds[3];
    float                   maxBounds[3];

    poolSliceData_t         slice;
};