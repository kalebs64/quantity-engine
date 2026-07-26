#pragma once

#include <Eigen/Core>
#include <Eigen/Dense>
using namespace Eigen;

Matrix4f LookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up);
Matrix4f Perspective(float fovyRadians, float aspect, float zNear, float zFar);