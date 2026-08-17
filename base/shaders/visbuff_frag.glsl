flat in uint io_instanceID;

layout(location = 0) out uvec2 io_fragVis;


void main() {
    io_fragVis = uvec2(io_instanceID, gl_PrimitiveID + 1);
    // io_fragVis = unpackUnorm2x16(CalculateOutputVBID(io_instanceID, gl_PrimitiveID + 1));
}