#include "shared.glsl"
#include "compute_common.glsl"

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(std430, binding = 0)         buffer g_commandBuffer            { indirectDispatch_t commands[]; };
layout(std430, binding = 1)         readonly buffer g_instanceBuffer  { instanceData_t instances[]; };

layout(rgba8, binding = 0)          writeonly uniform image2D u_screenTexture;
layout(binding = 1)                 uniform usampler2D u_visBuffer;

vec3 GetMaterialColor(uint id) {
    if(id == 0xFFFFFFFFu) return vec3(0.0);
    float r = fract(sin(float(id) * 12.9898) * 43758.5453);
    float g = fract(sin(float(id) * 78.2330) * 43758.5453);
    float b = fract(sin(float(id) * 45.1640) * 43758.5453);
    return vec3(r, g, b) * 0.8 + 0.2;
}

void main() {
    ivec2 pixelCoord = ivec2(gl_GlobalInvocationID.xy);
    ivec2 screenSize = imageSize(u_screenTexture);

    if(pixelCoord.x >= screenSize.x || pixelCoord.y >= screenSize.y) return;

    uvec4 visData = texelFetch(u_visBuffer, pixelCoord, 0);
    uint instanceId = visData.r;

    if(visData.x == 0u && visData.y == 0u) {
        imageStore(u_screenTexture, pixelCoord, vec4(0.0, 0.0, 0.0, 1.0));
        return;
    }

    uint materialID = instances[instanceId].m_materialID;
    indirectDispatch_t matDispatch = commands[materialID];
    vec3 color = GetMaterialColor(materialID);

    if(pixelCoord.x % 16 == 0 || pixelCoord.y % 16 == 0) {
        color *= 0.2;
    }
    imageStore(u_screenTexture, pixelCoord, vec4(color, 1.0));
}