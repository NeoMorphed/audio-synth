#ifndef _COMMON_MATH__H
#define _COMMON_MATH__H

#include "math/Vectors.h"
#include "math/Matrix4.h"

#define PI 3.14159265897f
namespace Tactics
{
	const float EPSILON = 0.0000001f;
	Vector2 transform_vec2(const Vector2 &position, const Matrix4 &matrix);
	float to_radians(float degrees);
	float to_degrees(float radians);
	float lerp(float v0, float v1, float t);	
}

#endif