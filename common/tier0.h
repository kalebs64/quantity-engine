#pragma once
#if 0
#include <Eigen/Core>
#include <Eigen/Dense>
using namespace Eigen;

Matrix4f LookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up);
Matrix4f Perspective(float fovyRadians, float aspect, float zNear, float zFar);
#endif

#include "platform/platform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using Vector2 = glm::vec2;
using Uint2   = glm::uvec2;
using Uint3   = glm::uvec3;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

using Matrix4x4 = glm::mat4;