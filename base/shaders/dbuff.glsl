#include "compute_common.glsl"

layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 0) buffer g_outCommandBuffer {
    indirectDispatch_t commands[];
};

//I don't know how good this is, it generates a dispatch list for materials within a pixel.
void main() {
    uint matId = gl_GlobalInvocationID.x;
    uint totalPixels = commands[matId].m_pixelCount;

    commands[matId].m_groupCountX = (totalPixels + 63u) / 64u;
    commands[matId].m_groupCountY = 1u;
    commands[matId].m_groupCountZ = 1u;
}