layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

struct drawIndirect_t {
    uint            m_count;
    uint            m_instanceCount;
    uint            m_firstIndex;
    uint            m_baseVertex;
    uint            m_baseInstance;
};

struct poolSliceData_t {
    uint            m_vertexCacheOffset;
    uint            m_indexCacheOffset;
    uint            m_indexCount;
};

struct instanceData_t {
    mat4            m_worldMatrix;
    uint            m_sliceID;
    uint            padding0;
    uint            m_materialID;
    uint            padding1;
};

struct frameConstants_t {
    mat4            m_viewProj;
    uint            m_frameInstanceCount;
    float           m_padding[3];
};

layout(std430, binding = 0) readonly buffer g_instanceBuffer     { instanceData_t instances[]; };
layout(std430, binding = 1) readonly buffer g_sliceBuffer        { poolSliceData_t slices[]; };
layout(std430, binding = 2) readonly buffer g_frameConstants     {
    frameConstants_t constants;
};
layout(std430, binding = 3) writeonly buffer g_commandBufferOut  { drawIndirect_t commands[]; };

void main() {
    uint instanceId = gl_GlobalInvocationID.x;

    if(instanceId >= constants.m_frameInstanceCount) {
        return;
    }

    instanceData_t instance = instances[instanceId];
    poolSliceData_t slice = slices[instance.m_sliceID];

    commands[instanceId].m_count         = slice.m_indexCount;
    commands[instanceId].m_instanceCount = 1;
    commands[instanceId].m_firstIndex    = slice.m_indexCacheOffset;
    commands[instanceId].m_baseVertex    = slice.m_vertexCacheOffset;
    commands[instanceId].m_baseInstance  = instanceId;
}