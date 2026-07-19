#pragma once
#include <types.h>

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