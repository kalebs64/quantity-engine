#include "shared.glsl"

layout(std430, binding = 0)     readonly buffer g_geometryBuffer { vertex_t vertices[]; };
layout(std430, binding = 1)     readonly buffer g_instanceBuffer { instanceData_t instances[]; };
layout(std430, binding = 2)     readonly buffer g_frameConstants {
    frameConstants_t constants;
};

flat out uint io_instanceID;

void main() {
    uint pInstanceId = gl_BaseInstance;

    mat4 worldMatrix = instances[pInstanceId].m_worldMatrix;
    vec3 localPos = vertices[gl_VertexID].m_pos;
    
    gl_Position = constants.m_viewProj * worldMatrix * vec4(localPos, 1.0);
    
    io_instanceID = pInstanceId;
}