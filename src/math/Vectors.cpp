#include "Vectors.h"

namespace Tactics
{
	iVector2 ivec2(int x, int y)
	{
		iVector2 ivector2;
		ivector2.x = x;
		ivector2.y = y;
		return ivector2;
	}
	Vector2 vec2(float x, float y)
	{
		Vector2 vector2;
		vector2.x = x;
		vector2.y = y;
		return vector2;
	}
	Vector2 vec2(float scalar)
	{
		Vector2 vector2;
		vector2.x = scalar;
		vector2.y = scalar;
		return vector2;
	}
	Vector3 vec3(float x, float y, float z)
	{
		Vector3 vector3;
		vector3.x = x;
		vector3.y = y;
		vector3.z = z;
		return vector3;
	}
	Vector3 vec3(float scalar)
	{
		Vector3 vector3;
		vector3.x = scalar;
		vector3.y = scalar;
		vector3.z = scalar;
		return vector3;
	}
	Vector3 vec3(Vector4 vec4)
	{
		Vector3 vector3;
		vector3.x = vec4.x;
		vector3.y = vec4.y;
		vector3.z = vec4.z;
		return vector3;	
	}
	Vector4 vec4(float x, float y, float z, float w)
	{
		Vector4 vector4;
		vector4.x = x;
		vector4.y = y;
		vector4.z = z;
		vector4.w = w;
		return vector4;
	}
	Vector4 vec4(float value)
	{
		Vector4 vector4;
		vector4.x = value;
		vector4.y = value;
		vector4.z = value;
		vector4.w = value;
		return vector4;
	}
	Vector4 vec4(Vector3 vec3, float w)
	{
		Vector4 vector4;
		vector4.x = vec3.x;
		vector4.y = vec3.y;
		vector4.z = vec3.z;
		vector4.w = w;
		return vector4;
	}
	Vector2 normalize_vec2(Vector2 a)
	{
		float magnitude = sqrt((a.x * a.x) + (a.y * a.y));
		Vector2 vec;
		vec.x = a.x / magnitude;
		vec.y = a.y / magnitude;
		return vec;
	}
	float magnitude_vec3(Vector3 a)
	{
		return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	}
	Vector3 normalize_vec3(Vector3 a)
	{
		float magnitude = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
		Vector3 vec;
		vec.x = a.x / magnitude;
		vec.y = a.y / magnitude;
		vec.z = a.z / magnitude;
		return vec;
	}
	Vector4 normalize_vec4(Vector4 a)
	{
		float magnitude = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w));
		Vector4 vec;
		vec.x = a.x / magnitude;
		vec.y = a.y / magnitude;
		vec.z = a.z / magnitude;
		vec.w = a.w / magnitude;
		return vec;
	}

	float length_vec3(Vector3 v)
	{
		return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	float dot_product_vec2(Vector2 a, Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
	float dot_product_vec3(Vector3 a, Vector3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	float dot_product_vec4(Vector4 a, Vector4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	Vector3 cross_product(Vector3 a, Vector3 b)
	{
		Vector3 vec;
		vec.x = a.y * b.z - a.z * b.y;
		vec.y = a.z * b.x - a.x * b.z;
		vec.z = a.x * b.y - a.y * b.x;
		return vec;
	}

	Vector2 operator+(const Vector2& a, const Vector2 &b)
	{
		Vector2 result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		return result;
	}
	Vector3 operator+(const Vector3& a, const Vector3 &b)
	{
		Vector3 result;
		result.x = a.x + b.x; 
		result.y = a.y + b.y;
		result.z = a.z + b.z;
		return result;
	}
	Vector4 operator+(const Vector4& a, const Vector4 &b)
	{
		Vector4 result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		result.z = a.z + b.z;
		result.w = a.w + b.w;
		return result;
	}
	void operator+=(Vector2 &a, const Vector2 &b)
	{
		a.x = a.x + b.x;
		a.y = a.y + b.y;
	}
	Vector2 operator*(const Vector2 &a, float scalar)
	{
		Vector2 result;
		result.x = a.x * scalar;
		result.y = a.y * scalar;
		return result;
	}
	Vector3 operator*(float scalar, const Vector3 &a)
	{
		Vector3 result;
		result.x = a.x * scalar;
		result.y = a.y * scalar;
		result.z = a.z * scalar;
		return result;
	}
	Vector3 operator*(const Vector3 &a, float scalar)
	{
		Vector3 result;
		result.x = a.x * scalar;
		result.y = a.y * scalar;
		result.z = a.z * scalar;
		return result;
	}
	void operator+=(Vector3 &a, const Vector3 &b)
	{
		a.x = a.x + b.x;
		a.y = a.y + b.y;
		a.z = a.z + b.z;
	}
	void operator+(Vector3 &a, const float b)
	{
		a.x = a.x + b;
		a.y = a.y + b;
		a.z = a.z + b;
	}
	void operator-=(Vector3 &a, const Vector3 &b)
	{
		a.x = a.x - b.x;
		a.y = a.y - b.y;
		a.z = a.z - b.z;
	}
	bool operator==(Vector3 &a, const Vector3 &b)
	{
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
	}
	Vector4 operator*(const Vector4 &a, float scalar)
	{
		Vector4 result;
		result.x = a.x * scalar;
		result.y = a.y * scalar;
		result.z = a.z * scalar;
		result.w = a.w * scalar;
		return result;
	}
	Vector2 operator-(const Vector2 &a, const Vector2 &b)
	{
		Vector2 result;
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		return result;
	}
	Vector3 operator-(const Vector3 &a, const Vector3 &b)
	{
		Vector3 result;
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
		return result;
	}
	Vector4 operator-(const Vector4 &a, const Vector4 &b)
	{
		Vector4 result;
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
		result.w = a.w - b.w;
		return result;
	}
	void operator-=(Vector2 &a, const Vector2 &b)
	{
		a.x = a.x - b.x;
		a.y = a.y - b.y;
	}

	std::ostream& operator<<(std::ostream& os, const Vector2 &vec)
	{
		os << "{ x:" << vec.x << ", y:" << vec.y <<  " }";
		return os;
	}
	std::ostream& operator<<(std::ostream& os, const Vector3 &vec)
	{
		os << "{ x:" << std::fixed << std::setprecision(3) << vec.x << ", y:" << vec.y << ", z:"<< vec.z << " }";
		return os;
	}
	std::ostream& operator<<(std::ostream& os, const Vector4 &vec)
	{
		os << "{ x:" << vec.x << ", y:" << vec.y << ", z:"<< vec.z << ", w:"<< vec.w << " }";
		return os;
	}
}