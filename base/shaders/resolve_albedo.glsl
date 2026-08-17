#include "resolve_common.glsl"

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


//TODO: WITH MATERIAL DISPATCH BEING ADDED, WE MAY HAVE TO UPDATE THIS IN ACCORDANCE
void main() {
    ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);
    ivec2 screenSize = imageSize(u_screenTexture);

    if(pixelCoords.x >= screenSize.x || pixelCoords.y >= screenSize.y) {
        return;
    }

    uvec2 visData = texelFetch(u_visBuffer, pixelCoords, 0).rg;
    uint instanceID = visData.x;
    uint primitiveID = visData.y - 1u;

    if(visData.x == 0u && visData.y == 0u) {
        imageStore(u_screenTexture, pixelCoords, vec4(0.0, 0.0, 0.0, 1.0));
        return;
    }

    instanceData_t instance = instances[instanceID];
    poolSliceData_t slice   = slices[instance.m_sliceID];
    material_t material     = materials[instance.m_materialID];

    uvec3 indexSet = GetTriangleIndices(slice, primitiveID);
    triangle_t tri = GetTriangle(indexSet);

    mat4 mvp = constants.m_viewProj * instance.m_worldMatrix;
    vec4 clip0 = mvp * vec4(tri.m_v0.m_pos.x, tri.m_v0.m_pos.y, tri.m_v0.m_pos.z, 1.0);
    vec4 clip1 = mvp * vec4(tri.m_v1.m_pos.x, tri.m_v1.m_pos.y, tri.m_v1.m_pos.z, 1.0);
    vec4 clip2 = mvp * vec4(tri.m_v2.m_pos.x, tri.m_v2.m_pos.y, tri.m_v2.m_pos.z, 1.0);

    vec2 pixel0 = ClipToScreenSpace(clip0, vec2(screenSize));
    vec2 pixel1 = ClipToScreenSpace(clip1, vec2(screenSize));
    vec2 pixel2 = ClipToScreenSpace(clip2, vec2(screenSize));

    vec2 currentPixelPos = vec2(pixelCoords) + vec2(0.5);
    vec3 weights = CalcFullBarycentrics(currentPixelPos, pixel0, pixel1, pixel2);

    vec2 uv0 = tri.m_v0.m_uv;
    vec2 uv1 = tri.m_v1.m_uv;
    vec2 uv2 = tri.m_v2.m_uv;
    // vec2 interpolatedUV = weights.x * uv0 + weights.y * uv1 + weights.z * uv2;
    vec2 interpolatedUV = InterpolateAttrib2(weights, uv0, uv1, uv2);

    vec3 n0 = tri.m_v0.m_normal;
    vec3 n1 = tri.m_v1.m_normal;
    vec3 n2 = tri.m_v2.m_normal;
    vec3 localMatrix = normalize(InterpolateAttrib3(weights, n0, n1, n2));
    mat3 normalMatrix = transpose(inverse(mat3(instance.m_worldMatrix)));
    vec3 worldNormal = normalize(normalMatrix * localMatrix);

    vec4 albedoTex = SampleTexture2D(material.m_albedoMap, interpolatedUV);
    vec3 finalColor = albedoTex.rgb * vec3(0.6, 0.2, 0.5);

    // imageStore(u_screenTexture, pixelCoords, vec4(worldNormal * 0.5 + 0.5, 1.0));
    imageStore(u_screenTexture, pixelCoords, vec4(finalColor, 1.0));
}