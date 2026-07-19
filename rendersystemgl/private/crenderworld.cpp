#include "irenderworld.h"
#include <vector>

struct renderProp_t {
    int32                       m_drawCount;

    mesh_t*                     m_requestedMesh;
    IMaterial*                  m_material;
};

struct renderData_t {
    std::vector<renderProp_t>  m_renderableProps; //static meshes don't have model matrices, so you just draw them. though they are expected to have any transformations baked into their vertices already.
    //std::vector m_posables;
};

class CRenderWorld : public IRenderWorld {
public:
    virtual void                Init();
    virtual void                Shutdown();
    virtual void                DrawProp(mesh_t* mesh, IMaterial* material = nullptr);
    virtual void                DrawStaticModel();
    virtual void                DrawPosingFigureModel();
    virtual void                Frame();
private:
    void                        SortAllRenderData();
    void                        SortPropRenderData();
    void                        SortPosableRenderData();

    void                        SetCurrentMaterial(IMaterial* material);

    void                        DrawStaticMeshes();
    void                        DrawPosableMeshes();
    void                        DrawSky();
    void                        DrawPosables();
private:
    renderData_t                m_currentRender;
};

CRenderWorld rw;
IRenderWorld* g_renderWorld = &rw;

void CRenderWorld::Init() {}

void CRenderWorld::Shutdown() {}

void CRenderWorld::DrawProp(mesh_t* mesh, IMaterial* material) {}

void CRenderWorld::DrawStaticModel() {}

void CRenderWorld::DrawPosingFigureModel() {}

void CRenderWorld::Frame() {}