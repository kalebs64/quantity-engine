#include "tier0.h"

Matrix4f LookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up) {
    Vector3f f = (target - eye).normalized();
    Vector3f s = f.cross(up).normalized();
    Vector3f u = s.cross(f);

    Matrix4f view = Matrix4f::Identity();
    
    view(0, 0) = s.x();  view(0, 1) = s.y();  view(0, 2) = s.z();  view(0, 3) = -s.dot(eye);
    view(1, 0) = u.x();  view(1, 1) = u.y();  view(1, 2) = u.z();  view(1, 3) = -u.dot(eye);
    view(2, 0) = -f.x(); view(2, 1) = -f.y(); view(2, 2) = -f.z(); view(2, 3) = f.dot(eye);
    
    return view;
}

Matrix4f Perspective(float fovyRadians, float aspect, float zNear, float zFar) {
    float tanHalfFovy = std::tan(fovyRadians / 2.0f);
    
    Matrix4f proj = Matrix4f::Zero();
    
    proj(0, 0) = 1.0f / (aspect * tanHalfFovy);
    proj(1, 1) = 1.0f / tanHalfFovy;
    proj(2, 2) = -(zFar + zNear) / (zFar - zNear);
    proj(3, 2) = -1.0f;
    proj(2, 3) = -(2.0f * zFar * zNear) / (zFar - zNear);
    
    return proj;
}