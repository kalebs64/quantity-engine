#pragma once
#include "imesh.h"
#include <tier0.h>

class IGeometryManager {
public:
    virtual void                Init() = 0;
    // Begin a mesh build
    virtual void                BeginMeshBuild(const char* pName) = 0;
    // Add a position value
    virtual void                VertexPosition3f(Vector3 pValue) = 0;
    // Add a normal value
    virtual void                VertexNormal3f(Vector3 pValue) = 0;
    // Add a uv value
    virtual void                VertexUV2f(Vector2 pValue) = 0;
    // Add an index
    virtual void                IndexUI(uint pValue) = 0;
    virtual void                NextVertex() = 0;
    virtual void                NextIndex() = 0;
    // Finalize your mesh, and get its slice.
    virtual poolSliceData_t*    FinishMeshBuild() = 0;

    virtual void                ResetManager() = 0;

    virtual void                SetVertexBuffer(uint pSlot) = 0;
    virtual void                SetIndexBuffer(uint pSlot) = 0;
    virtual void                SetSliceBuffer(uint pSlot) = 0;
};

#define QUANTITY_GEOMETRY_MANAGER "QUANTITY_GEOMETRYMANAGER_001"
extern IGeometryManager* g_geometryManager;