#include "shared.glsl"
#include "compute_common.glsl"

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(std430, binding = 0)         buffer g_outCommandBuffer { indirectDispatch_t commands[]; };
layout(std430, binding = 1)         buffer g_outPixelBuffer { uint outPixelCoords[]; };
layout(std430, binding = 2)         readonly buffer g_instanceBuffer  { instanceData_t instances[]; };
layout(binding = 1)                 uniform usampler2D u_visBuffer;

//generates a buckets for materials within.
void main() {
    ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);
    ivec2 screenSize = textureSize(u_visBuffer, 0);

    if(pixelCoords.x >= screenSize.x || pixelCoords.y >= screenSize.y) {
        return;
    }

    uvec2 visData = texelFetch(u_visBuffer, pixelCoords, 0).rg;
    uint instanceID = visData.x;

    if(visData.x == 0u && visData.y == 0u) {
        return;
    }
    instanceData_t instance = instances[instanceID];

    uint materialId = instance.m_materialID;
    
    uint packedCoords = ((pixelCoords.x) << 16 | (pixelCoords.y) & 0xFFFFu);

    uint localIdx = atomicAdd(commands[materialId].m_pixelCount, 1);
    uint writeIdx = commands[materialId].m_pixelBufferOffset + localIdx;
    outPixelCoords[writeIdx] = packedCoords;
}