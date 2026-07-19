#pragma once
#include "imesh.h"

class IMaterial;
struct mesh_t;
class ITexture;

class IRenderWorld {
public:
    virtual void                Init() = 0;
    virtual void                Shutdown() = 0;

    virtual void                DrawProp(mesh_t* mesh, IMaterial* material = nullptr) = 0;

    virtual void                DrawStaticModel() = 0;

    virtual void                DrawPosingFigureModel() = 0;

    virtual void                Frame() = 0;
};

#define QUANTITY_RENDERWORLD_VERSION "QUANTITY_RENDERWORLD_001"
extern IRenderWorld* g_renderWorld;