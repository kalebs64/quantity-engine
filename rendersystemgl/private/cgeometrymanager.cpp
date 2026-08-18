#include "igeometrymanager.h"
#include "cgpubuffer.h"
#include "enums.h"
#include <tier1.h>

#define MAX_VERTEX_BUFFER 1024*1024
#define MAX_INDEX_BUFFER 1024*1024
#define MAX_SLICE_BUFFER 1024

class CGeometryManager : public IGeometryManager {
public:
    virtual void                Init();
    virtual void                BeginMeshBuild(const char* pName);
    virtual void                VertexPosition3f(Vector3 pValue);
    virtual void                VertexNormal3f(Vector3 pValue);
    virtual void                VertexUV2f(Vector2 pValue);
    virtual void                IndexUI(uint pValue);
    virtual void                NextVertex();
    virtual void                NextIndex();
    virtual poolSliceData_t*    FinishMeshBuild();
    virtual void                ResetManager();
    virtual void                UpdateBuffers();
    virtual void                SetVertexBuffer(uint pSlot);
    virtual void                SetIndexBuffer(uint pSlot);
    virtual void                SetSliceBuffer(uint pSlot);
private:
    const char*                 m_currName;

    int                         m_addedVerts;
    int                         m_addedIdxs;

    vertex_t                    m_targetVertex;
    uint                        m_currentIndex;

    CGPUBuffer                  m_gpuVerts;
    CGPUBuffer                  m_gpuIndices;
    CGPUBuffer                  m_gpuSlices;

    List<vertex_t>              m_verticesCPU;
    List<poolSliceData_t>       m_slicesCPU;
    List<uint>                  m_indicesCPU;

    UnorderedMap<String, poolSliceData_t*> m_slices;
};


CGeometryManager cgm;
IGeometryManager* g_geometryManager = &cgm;

void CGeometryManager::Init() {
    m_gpuVerts.Init("buffer_vertex", 0, sizeof(vertex_t), QRBF_DYNAMIC | QRBF_READ, MAX_VERTEX_BUFFER);
    m_gpuIndices.Init("buffer_index", 1, sizeof(uint), QRBF_DYNAMIC | QRBF_READ, MAX_INDEX_BUFFER);
    m_gpuSlices.Init("buffer_slices", 2, sizeof(poolSliceData_t), QRBF_DYNAMIC | QRBF_READ, MAX_SLICE_BUFFER);

    BeginMeshBuild("default_cube");
    VertexPosition3f(Vector3(-0.5f, -0.5f,  0.5f));
    VertexNormal3f(Vector3(0,0,1));
    VertexUV2f(Vector2(0,0));
    NextVertex();
    VertexPosition3f(Vector3(0.5f, -0.5f,  0.5f));
    VertexNormal3f(Vector3(0,0,1));
    VertexUV2f(Vector2(1,0));
    NextVertex();
    VertexPosition3f(Vector3(0.5f,  0.5f,  0.5f));
    VertexNormal3f(Vector3(0,0,1));
    VertexUV2f(Vector2(1,1));
    NextVertex();
    VertexPosition3f(Vector3(-0.5f,  0.5f,  0.5f));
    VertexNormal3f(Vector3(0,0,1));
    VertexUV2f(Vector2(0,1));
    NextVertex();
    VertexPosition3f(Vector3(-0.5f, -0.5f, -0.5f));
    VertexNormal3f(Vector3(0,0,-1));
    VertexUV2f(Vector2(0,0));
    NextVertex();
    VertexPosition3f(Vector3(0.5f, -0.5f, -0.5f));
    VertexNormal3f(Vector3(0,0,-1));
    VertexUV2f(Vector2(1,0));
    NextVertex();
    VertexPosition3f(Vector3(0.5f,  0.5f, -0.5f));
    VertexNormal3f(Vector3(0,0,-1));
    VertexUV2f(Vector2(1,1));
    NextVertex();
    VertexPosition3f(Vector3(-0.5f,  0.5f, -0.5f));
    VertexNormal3f(Vector3(0,0,-1));
    VertexUV2f(Vector2(0,1));
    FinishMeshBuild();
}

void CGeometryManager::BeginMeshBuild(const char* pName) {
    m_currName = pName;
}

void CGeometryManager::VertexPosition3f(Vector3 pValue) {}

void CGeometryManager::VertexNormal3f(Vector3 pValue) {}

void CGeometryManager::VertexUV2f(Vector2 pValue) {}

void CGeometryManager::IndexUI(uint pValue) {}

void CGeometryManager::NextVertex() {}

void CGeometryManager::NextIndex() {}

poolSliceData_t* CGeometryManager::FinishMeshBuild() {
    poolSliceData_t slice = {};
    uint sliceCount = 0;

    //we just add data to the end of GPU buffers
    vertex_t* vregion = m_verticesCPU.data() + (m_verticesCPU.size() - m_addedVerts);
    uint* iregion = m_indicesCPU.data() + (m_indicesCPU.size() - m_addedIdxs);
    poolSliceData_t* pregion = m_slicesCPU.data() + (m_slicesCPU.size() - 1);

    slice.vertexCacheOffset = m_verticesCPU.size();
    slice.indexCacheOffset  = m_indicesCPU.size();
    slice.indexCount        = m_addedIdxs;
    m_slicesCPU.push_back(slice);

    sliceCount = m_slicesCPU.size();

    m_gpuVerts.WriteBufferDataTail(vregion, sizeof(vertex_t) * m_addedVerts);
    m_gpuIndices.WriteBufferDataTail(iregion, sizeof(uint) * m_addedIdxs);
    m_gpuSlices.WriteBufferDataTail(pregion, sizeof(poolSliceData_t) * 1);

    m_slices[m_currName] = &m_slicesCPU[sliceCount];
    return m_slices[m_currName];
}

void CGeometryManager::ResetManager() {}

void CGeometryManager::UpdateBuffers() {
    m_gpuVerts.OverwriteBufferData(m_verticesCPU.data(), m_verticesCPU.size());
    m_gpuIndices.OverwriteBufferData(m_indicesCPU.data(), m_indicesCPU.size());
}

void CGeometryManager::SetVertexBuffer(uint pSlot) {}

void CGeometryManager::SetIndexBuffer(uint pSlot) {}

void CGeometryManager::SetSliceBuffer(uint pSlot) {}