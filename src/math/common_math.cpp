#include "common_math.h"

namespace Tactics
{
	Vector2 transform_vec2(const Vector2 &position, const Matrix4 &matrix)
	{
		Vector2 result = vec2((position.x * matrix.m11) + (position.y * matrix.m12) + matrix.m14,
							(position.x * matrix.m21) + (position.y * matrix.m22) + matrix.m24);
		return result;
	}
	float to_radians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}
	float to_degrees(float radians)
	{
		return radians * (180.0f / PI);
	}
	float lerp(float v0, float v1, float t) 
	{
  		return (1 - t) * v0 + t * v1;
  	}
  	// float pow2(float x, float y)
  	// {
  	// 	float result = x;
  	// 	if (y < 0.0f) {
  	// 		y = -y;
  	// 		for (int i = 0; i < (int)y - 1; i++) {
  	// 			result = result * x;
  	// 		}
  	// 		result = 1.0f / result;
  	// 		//printf("%f\n", result);
  	// 		printf("x = %f result = %f\n", x, result);
  	// 	}
  	// 	return result;
  	// }
}