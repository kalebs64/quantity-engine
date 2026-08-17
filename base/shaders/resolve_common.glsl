#include "shared.glsl"

layout(std430, binding = 0) readonly buffer g_geometryBuffer  { vertex_t vertices[]; };
layout(std430, binding = 1) readonly buffer g_instanceBuffer  { instanceData_t instances[]; };
layout(std430, binding = 2) readonly buffer g_indexBuffer     { uint indices[]; };
layout(std430, binding = 3) readonly buffer g_sliceBuffer     { poolSliceData_t slices[]; };
layout(std430, binding = 4) readonly buffer g_frameConstants  { frameConstants_t constants; };
layout(std430, binding = 5) readonly buffer g_materialBuffer  { material_t materials[]; };

layout(rgba8, binding = 0)          writeonly uniform image2D u_screenTexture;
layout(binding = 1)                 uniform usampler2D u_visBuffer;

struct triangle_t {
    vertex_t m_v0;
    vertex_t m_v1;
    vertex_t m_v2;
};

vec3 CalcFullBarycentrics(vec2 pPoint, vec2 pA, vec2 pB, vec2 pC) {
    vec2 edge0 = pB - pA;
    vec2 edge1 = pC - pA;
    vec2 delta = pPoint - pA;

    float invDenominator = 1.0 / (edge0.x * edge1.y - edge1.x * edge0.y);
    float v = (delta.x * edge1.y - edge1.x * delta.y) * invDenominator;
    float w = (edge0.x * delta.y - delta.x * edge0.y) * invDenominator;
    float u = 1.0 - v - w;

    return vec3(u, v, w);
}

mat3 ConstructTBN(vec3 pPosA, vec3 pPosB, vec3 pPosC, vec2 pUVA, vec2 pUVB, vec2 pUVC, vec3 pNormal) {
    vec3 deltaPos1 = pPosB - pPosA;
    vec3 deltaPos2 = pPosC - pPosA;
    vec2 deltaUV1  = pUVB - pUVA;
    vec2 deltaUV2  = pUVC - pUVA;

    float invDeterminant = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
    vec3 tangent   = normalize((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * invDeterminant);
    vec3 bitangent = normalize(cross(pNormal, tangent));

    return mat3(tangent, bitangent, pNormal);
}

uvec3 GetTriangleIndices(poolSliceData_t pSlice, uint pPrimitiveID) {
    uint triangleIndex = pSlice.m_indexCacheOffset + (pPrimitiveID * 3u);

    uint index0 = indices[triangleIndex + 0u] + pSlice.m_vertexCacheOffset;
    uint index1 = indices[triangleIndex + 1u] + pSlice.m_vertexCacheOffset;
    uint index2 = indices[triangleIndex + 2u] + pSlice.m_vertexCacheOffset;

    return uvec3(index0, index1, index2);
}

vec2 ClipToScreenSpace(vec4 pClipPos, vec2 pScreenSize) {
    vec2 ndc = pClipPos.xy / pClipPos.w;
    return (ndc * 0.5 + vec2(0.5)) * pScreenSize;
}

vec2 InterpolateAttrib2(vec3 pWeights, vec2 pAttribA, vec2 pAttribB, vec2 pAttribC) {
    return (pWeights.x * pAttribA + pWeights.y * pAttribB + pWeights.z * pAttribC);
}

vec3 InterpolateAttrib3(vec3 pWeights, vec3 pAttribA, vec3 pAttribB, vec3 pAttribC) {
    return (pWeights.x * pAttribA + pWeights.y * pAttribB + pWeights.z * pAttribC);
}

triangle_t GetTriangle(uvec3 pIndices) {
    triangle_t tri;
    tri.m_v0 = vertices[pIndices.x];
    tri.m_v1 = vertices[pIndices.y];
    tri.m_v2 = vertices[pIndices.z];
    return tri;
}