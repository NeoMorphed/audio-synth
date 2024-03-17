#ifndef MATRIX_H
#define MATRIX_H

namespace Tactics
{
	struct Vector3;
	union Vector4;
	//Matrix is in column major order
	struct Matrix4
	{
		float m11;
		float m12;
		float m13;
		float m14;
		float m21;
		float m22;
		float m23;
		float m24;
		float m31;
		float m32;
		float m33;
		float m34;
		float m41;
		float m42;
		float m43;
		float m44;
	};
	// union Matrix4
	// {
	// 	struct 
	// 	{
	// 		float[4][4]
	// 	};
	// 	struct 
	// 	{
	// 		float m11;
	// 		float m12;
	// 		float m13;
	// 		float m14;
	// 		float m21;
	// 		float m22;
	// 		float m23;
	// 		float m24;
	// 		float m31;
	// 		float m32;
	// 		float m33;
	// 		float m34;
	// 		float m41;
	// 		float m42;
	// 		float m43;
	// 		float m44;
	// 	};
	// };

	Matrix4 matrix4_zeroed();
	// Matrix4 mat4(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4);
	Matrix4 translate_matrix(Matrix4 matrix, Vector3 translation);
	Matrix4 scale_matrix(float scale);
	Matrix4 scale_matrix(Matrix4 matrix, Vector3 scale);
	Matrix4 ortho_matrix(float left, float right, float bottom, float top, float zNear, float zFar);
	Matrix4 perspective_matrix(float fov, float aspect_ratio, float near, float far);
	Matrix4 identity_matrix();
	Matrix4 transpose_matrix(Matrix4 m);
	Matrix4 inverse_matrix(Matrix4 matrix);

	//Matrix4 copy_matrix4(Matrix4)
	Matrix4 operator*(const Matrix4 &a, const Matrix4 &b);
	Vector4 operator*(const Matrix4 &m, const Vector4 &b);
	std::ostream& operator<<(std::ostream& os, const Matrix4 &matrix);
}
#endif