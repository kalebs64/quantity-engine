#include "tier0.h"

#if 0
Matrix4f LookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up) {
    Vector3f f = (target - eye).normalized();
    Vector3f s = f.cross(up).normalized();
    Vector3f u = s.cross(f);

    Matrix4f res = Matrix4f::Identity();

    res(0, 0) = s.x();  res(0, 1) = u.x();  res(0, 2) = -f.x();  res(0, 3) = 0.0f;
    res(1, 0) = s.y();  res(1, 1) = u.y();  res(1, 2) = -f.y();  res(1, 3) = 0.0f;
    res(2, 0) = s.z();  res(2, 1) = u.z();  res(2, 2) = -f.z();  res(2, 3) = 0.0f;
    res(3, 0) = -s.dot(eye); 
    res(3, 1) = -u.dot(eye); 
    res(3, 2) = f.dot(eye);  
    res(3, 3) = 1.0f;
    
    return res;
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
#endif