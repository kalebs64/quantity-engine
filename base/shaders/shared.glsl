#extension GL_ARB_bindless_texture : require
#extension GL_ARB_texture_query_levels : enable

struct vertex_t {
    vec3 m_pos;
    vec3 m_normal;
    vec2 m_uv;
};

struct poolSliceData_t {
    uint                          m_vertexCacheOffset;
    uint                          m_indexCacheOffset;
    uint                          m_indexCount;
};

struct instanceData_t {
    mat4                          m_worldMatrix;
    uint                          m_sliceID;
    uint                          m_materialID;
    uint                          m_padding0;
    uint                          m_padding1;
};

struct frameConstants_t {
    mat4            m_viewProj;
    uint            m_frameInstanceCount;
    float           m_padding[3];
};

struct material_t {
    uvec2           m_albedoMap;
    float           m_padding0;
    vec4            m_albedoFactor;
    float           m_roughFactor;
    float           m_metallicFactor;
};

sampler2D GetFullTexture(uvec2 pHandleVec) {
    return sampler2D(pHandleVec);
}

vec4 SampleTexture2D(uvec2 pHandleVec, vec2 pUV) {
    if(pHandleVec == uvec2(0u, 0u)) {
        return vec4(1.0);
    }
    return texture(GetFullTexture(pHandleVec), pUV);
}