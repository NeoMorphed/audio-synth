#ifndef _____VECTORS______H
#define _____VECTORS______H

namespace Tactics
{
	struct Vector2
	{
		float x;
		float y;
	};
	struct Vector3
	{
		float x;
		float y;
		float z;
	};
	union Vector4
	{
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct 
		{
			float r;
			float g;
			float b;
			float a;
		};
	};
	struct iVector2
	{
		int x;
		int y;
	};
	iVector2 ivec2(int x, int y);
	Vector2 vec2(float x, float y);
	Vector2 vec2(float scalar);
	Vector3 vec3(float x, float y, float z);
	Vector3 vec3(float scalar);
	Vector3 vec3(Vector4 vec4);
	Vector4 vec4(float x, float y, float z, float w);
	Vector4 vec4(float value);
	Vector4 vec4(Vector3 vec3, float w);

	float dot_product_vec2(Vector2 a, Vector2 b);
	float dot_product_vec3(Vector3 a, Vector3 b);
	float dot_product_vec4(Vector4 a, Vector4 b);
	Vector3 cross_product(Vector3 a, Vector3 b);

	Vector2 normalize_vec2(Vector2 a);
	Vector3 normalize_vec3(Vector3 a);
	Vector4 normalize_vec4(Vector4 a);

	float length_vec3(Vector3 a);

	Vector2 operator+(const Vector2 &a, const Vector2 &b);
	Vector3 operator+(const Vector3 &a, const Vector3 &b);
	Vector4 operator+(const Vector4 &a, const Vector4 &b);
	void operator+=(Vector2 &a, const Vector2 &b);
	void operator*=(Vector2 &a, const Vector2 &b);
	Vector2 operator*(const Vector2 &a, float scalar);
	Vector3 operator*(const Vector3 &a, float scalar);
	Vector3 operator*(float scalar, const Vector3 &a);
	void operator+=(Vector3 &a, const Vector3 &b);
	void operator+(Vector3 &a, const float b);
	void operator-=(Vector3 &a, const Vector3 &b);
	bool operator==(Vector3 &a, const Vector3 &b);
	Vector4 operator*(const Vector4 &a, float scalar);
	Vector2 operator-(const Vector2 &a, const Vector2 &b);
	Vector3 operator-(const Vector3 &a, const Vector3 &b);
	Vector4 operator-(const Vector4 &a, const Vector4 &b);
	void operator-=(Vector2 &a, const Vector2 &b);

	std::ostream& operator<<(std::ostream& os, const Vector2 &vec);
	std::ostream& operator<<(std::ostream& os, const Vector3 &vec);
	std::ostream& operator<<(std::ostream& os, const Vector4 &vec);
}

#endif