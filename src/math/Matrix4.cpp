#include "Matrix4.h"
#include "Vectors.h"
namespace Tactics
{
	Matrix4 zero_matrix()
	{
		Matrix4 matrix;
		matrix.m11 = 0;
		matrix.m12 = 0;
		matrix.m13 = 0;
		matrix.m14 = 0;
		matrix.m21 = 0;
		matrix.m22 = 0;
		matrix.m23 = 0;
		matrix.m24 = 0;
		matrix.m31 = 0;
		matrix.m32 = 0;
		matrix.m33 = 0;
		matrix.m34 = 0;
		matrix.m41 = 0;
		matrix.m42 = 0;
		matrix.m43 = 0;
		matrix.m44 = 0;
		return matrix;
	}
	// Matrix4 mat4(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4)
	// {
	// 	m11 = row1.x;
	// 	m21 = row1.y;
	// 	m31 = row1.z;
	// 	m41 = row1.w;
	// 	m12 = row2.x;
	// 	m22 = row2.y;
	// 	m32 = row2.z;
	// 	m42 = row2.w;
	// 	m13 = row3.x;
	// 	m23 = row3.y;
	// 	m33 = row3.z;
	// 	m43 = row3.w;
	// 	m14 = row4.x;
	// 	m24 = row4.y;
	// 	m34 = row4.z;
	// 	m44 = row4.w;
	// }
	Matrix4 translate_matrix(Matrix4 in_matrix, Vector3 translation)
	{
		Matrix4 translate_matrix = zero_matrix();
		translate_matrix.m11 = 1;
		translate_matrix.m22 = 1;
		translate_matrix.m33 = 1;
		translate_matrix.m41 = translation.x;
		translate_matrix.m42 = translation.y;
		translate_matrix.m43 = translation.z;
		translate_matrix.m44 = 1;

		return in_matrix * translate_matrix;
	}
	// Matrix4 Matrix::RotationX(float radians)
	// {
	// 	Matrix matrix = Identity();
	// 	float val1 = (float)std::cos(radians);
	// 	float val2 = (float)std::sin(radians);

	// 	matrix.m22 = val1;
	// 	matrix.m23 = val2;
	// 	matrix.m32 = -val2;
	// 	matrix.m44 = val1;
	// 	return matrix;

	// }
	// Matrix Matrix::RotationY(float radians)
	// {
	// 	Matrix matrix = Identity();
	// 	float val1 = (float)std::cos(radians);
	// 	float val2 = (float)std::sin(radians);

	// 	matrix.m11 = val1;
	// 	matrix.m13 = val2;
	// 	matrix.m31 = -val2;
	// 	matrix.m33 = val1;
	// 	return matrix;
	// }
	// Matrix Matrix::RotationZ(float radians)
	// {
	// 	Matrix matrix = Identity();
	// 	float val1 = (float)std::cos(radians);
	// 	float val2 = (float)std::sin(radians);

	// 	matrix.m11 = val1;
	// 	matrix.m12 = val2;
	// 	matrix.m21 = -val2;
	// 	matrix.m22 = val1;
	// 	return matrix;
	// }
	// Matrix Matrix::Scale(float scale)
	// {
	// 	return Scale(scale, scale, scale);
	// }
	Matrix4 scale_matrix(Matrix4 in_matrix, Vector3 scale)
	{
		Matrix4 scale_matrix = zero_matrix();
		scale_matrix.m11 = scale.x;
		scale_matrix.m22 = scale.y;
		scale_matrix.m33 = scale.z;
		scale_matrix.m44 = 1;

		return in_matrix * scale_matrix;
	}
	Matrix4 perspective_matrix(float fov, float aspect_ratio, float near_z, float far_z)
	{
		assert(aspect_ratio != 0);
		Matrix4 matrix = zero_matrix();
		matrix.m11 = 1 / (aspect_ratio * tan(fov / 2));
		matrix.m22 = 1 / tan(fov / 2);
		matrix.m33 = -((far_z + near_z) / (far_z - near_z));
		matrix.m34 = -1;
		matrix.m43 = -((2 * far_z * near_z) / (far_z - near_z));
		return matrix; 
	}
	Matrix4 ortho_matrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		Matrix4 matrix = zero_matrix();
		matrix.m11 = 2 / (right - left);
		matrix.m22 = 2 / (top - bottom);
		matrix.m33 = -2 / (zFar - zNear);
		matrix.m41 = -((right + left) / (right - left));
		matrix.m42 = -((top + bottom) / (top - bottom));
		matrix.m43 = -((zFar + zNear) / (zFar - zNear));
		matrix.m44 = 1;
		return matrix;
	}
	Matrix4 identity_matrix()
	{
		Matrix4 matrix;
		matrix.m11 = 1;
		matrix.m12 = 0;
		matrix.m13 = 0;
		matrix.m14 = 0;
		matrix.m21 = 0;
		matrix.m22 = 1;
		matrix.m23 = 0;
		matrix.m24 = 0;
		matrix.m31 = 0;
		matrix.m32 = 0;
		matrix.m33 = 1;
		matrix.m34 = 0;
		matrix.m41 = 0;
		matrix.m42 = 0;
		matrix.m43 = 0;
		matrix.m44 = 1;
		return matrix;
	}
	Matrix4 transpose_matrix(Matrix4 m)
	{
		Matrix4 mat;
		// mat.m11 = m.m11;
		// mat.m12 = m.m21;
		// mat.m13 = m.m31;
		// mat.m14 = m.m41;
		// mat.m21 = m.m12;
		// mat .m
		mat.m11 = m.m11;
		mat.m12 = m.m21;
		mat.m13 = m.m31;
		mat.m14 = m.m41;
		mat.m21 = m.m12;
		mat.m22 = m.m22;
		mat.m23 = m.m32;
		mat.m24 = m.m42;
		mat.m31 = m.m13;
		mat.m32 = m.m23;
		mat.m33 = m.m33;
		mat.m34 = m.m43;
		mat.m41 = m.m14;
		mat.m42 = m.m24;
		mat.m43 = m.m34;
		mat.m44 = m.m44;
		return mat;
	}
	Matrix4 inverse_matrix(Matrix4 m)
	{

		// THESE NUMBERS ARE ALL BACKWARDS, KINDA OF AWKWARD.
		//swaping rows and columns
		// float m11 = m.m11;
		// float m12 = m.m21;
		// float m13 = m.m31;
		// float m14 = m.m41;
		// float m21 = m.m12;
		// float m22 = m.m22;
		// float m23 = m.m32;
		// float m24 = m.m42;
		// float m31 = m.m13;
		// float m32 = m.m23;
		// float m33 = m.m33;
		// float m34 = m.m43;
		// float m41 = m.m14;
		// float m42 = m.m24;
		// float m43 = m.m34;
		// float m44 = m.m44;

		float m11 = m.m11;
		float m12 = m.m12;
		float m13 = m.m13;
		float m14 = m.m14;
		float m21 = m.m21;
		float m22 = m.m22;
		float m23 = m.m23;
		float m24 = m.m24;
		float m31 = m.m31;
		float m32 = m.m32;
		float m33 = m.m33;
		float m34 = m.m34;
		float m41 = m.m41;
		float m42 = m.m42;
		float m43 = m.m43;
		float m44 = m.m44;

		//2x2 determinants of minor matricies
		//For rows 1 and 2
		float dtp1  = (m33 * m44) - (m34 * m43);
 		float dtp2  = (m23 * m44) - (m24 * m43);
 		float dtp3  = (m23 * m34) - (m24 * m33);
 
 		float dtp4  = (m13 * m44) - (m14 * m43);
 		float dtp5  = (m13 * m34) - (m14 * m33);

		// 4 2 1 6
		// 8 2 4 5
		// 1 7 9 4
		// 5 4 8 8
 
 		float dtp6  = (m13 * m24) - (m14 * m23);
 
		//For row 3 
		float dtp7  = (m32 * m44) - (m34 * m42);
		float dtp8  = (m22 * m44) - (m24 * m42);
		float dtp9  = (m22 * m34) - (m24 * m32);

		float dtp10 = (m12 * m44) - (m14 * m42);
		float dtp11 = (m12 * m34) - (m14 * m32);

		float dtp12 = (m12 * m24) - (m14 * m22);

		//For row 4
		// 10 in example
		float dtp13 = (m32 * m43) - (m33 * m42);
		// 11 in example
		float dtp14 = (m22 * m43) - (m23 * m42);
		// 12 in example;
		float dtp15 = (m22 * m33) - (m23 * m32);

		float dtp16 = (m12 * m43) - (m13 * m42);
		float dtp17 = (m12 * m33) - (m13 * m32);
		float dtp18 = (m12 * m23) - (m13 * m22);

		//Minor determinants
		//First row
		// float minorDet1  =  ((m22 * dtp1)  - (m32 * dtp2) + (m42 * dtp3));
		// float minorDet2  =  -((m12 * dtp1)  - (m32 * dtp4) + (m42 * dtp5));
		// float minorDet3  =  ((m12 * dtp2)  - (m22 * dtp4) + (m42 * dtp6));
		// float minorDet4  =  -((m12 * dtp3)  - (m22 * dtp5) + (m32 * dtp6));
		float minorDet1  =  ((m22 * dtp1)  - (m32 * dtp2) + (m42 * dtp3));
		float minorDet2  =  ((m12 * dtp1)  - (m32 * dtp4) + (m42 * dtp5));
		float minorDet3  =  ((m12 * dtp2)  - (m22 * dtp4) + (m42 * dtp6));
		float minorDet4  =  ((m12 * dtp3)  - (m22 * dtp5) + (m32 * dtp6));

		//Second row 
		float minorDet5  =  ((m21 * dtp1)  - (m31 * dtp2) + (m41 * dtp3));
		float minorDet6  =  ((m11 * dtp1)  - (m31 * dtp4) + (m41 * dtp5));
		float minorDet7  =  ((m11 * dtp2)  - (m21 * dtp4) + (m41 * dtp6));
		float minorDet8  =  ((m11 * dtp3)  - (m21 * dtp5) + (m31 * dtp6));
		//Third row 
		float minorDet9  =  ((m21 * dtp7)  - (m31 * dtp8)  + (m41 * dtp9));
		float minorDet10 =  ((m11 * dtp7)  - (m31 * dtp10) + (m41 * dtp11));
		float minorDet11 =  ((m11 * dtp8)  - (m21 * dtp10) + (m41 * dtp12));
		float minorDet12 =  ((m11 * dtp9)  - (m22 * dtp11) + (m41 * dtp12));
		//Fourth row
		float minorDet13 =  ((m21 * dtp13) - (m31 * dtp14) + (m41 * dtp15));
		//float minorDet14 =  ((m12 * dtp13) - (m31 * dtp16) + (m41 * dtp17));
		float minorDet14 =  ((m11 * dtp13) - (m31 * dtp16) + (m41 * dtp17));
		float minorDet15 =  ((m11 * dtp14) - (m21 * dtp16) + (m41 * dtp18));
		//float minorDet16 =  ((m12 * dtp15) - (m21 * dtp17) + (m31 * dtp18));
		float minorDet16 =  ((m11 * dtp15) - (m21 * dtp17) + (m31 * dtp18));


		float mDetInv = 1 / ((m11 * minorDet1) - (m21 * minorDet2) + (m31 * minorDet3) - (m41 * minorDet4));

		Matrix4 o;
		// Checked these elements for correcteness
		o.m11 = minorDet1 * mDetInv;
		o.m21 = -minorDet5 * mDetInv;
		o.m31 = minorDet9 * mDetInv;
		o.m41 = -minorDet13 * mDetInv;
		o.m12 = -minorDet2 * mDetInv;
		o.m22 = minorDet6 * mDetInv;
		o.m32 = -minorDet10 * mDetInv;
		o.m42 = minorDet14 * mDetInv;

		o.m13 = minorDet3 * mDetInv;
		o.m23 = -minorDet7 * mDetInv;
		o.m33 = minorDet11 * mDetInv;
		o.m43 = -minorDet15 * mDetInv;

		// Need to be checked
		o.m14 = -minorDet4 * mDetInv;
		o.m24 = minorDet8 * mDetInv;
		o.m34 = -minorDet12 * mDetInv;
		o.m44 = minorDet16 * mDetInv;

		return o; 
	}
	Matrix4 operator*(const Matrix4 &a, const Matrix4 &b)
	{
		Matrix4 result;

		// result.m11 = (((a.m11 * b.m11) + (a.m21 * b.m12)) + (a.m31 * b.m13)) + (a.m41 * b.m14);
		// result.m12 = (((a.m12 * b.m11) + (a.m22 * b.m12)) + (a.m32 * b.m13)) + (a.m42 * b.m14);
		// result.m13 = (((a.m13 * b.m11) + (a.m23 * b.m12)) + (a.m33 * b.m13)) + (a.m43 * b.m14);
		// result.m14 = (((a.m14 * b.m11) + (a.m24 * b.m12)) + (a.m34 * b.m13)) + (a.m44 * b.m14);
		// result.m21 = (((a.m11 * b.m21) + (a.m21 * b.m22)) + (a.m31 * b.m23)) + (a.m41 * b.m24);
		// result.m22 = (((a.m12 * b.m21) + (a.m22 * b.m22)) + (a.m32 * b.m23)) + (a.m42 * b.m24);
		// result.m23 = (((a.m13 * b.m21) + (a.m23 * b.m22)) + (a.m33 * b.m23)) + (a.m43 * b.m24);
		// result.m24 = (((a.m14 * b.m21) + (a.m24 * b.m22)) + (a.m34 * b.m23)) + (a.m44 * b.m24);
		// result.m31 = (((a.m11 * b.m31) + (a.m21 * b.m32)) + (a.m31 * b.m33)) + (a.m41 * b.m34);
		// result.m32 = (((a.m12 * b.m31) + (a.m22 * b.m32)) + (a.m32 * b.m33)) + (a.m42 * b.m34);
		// result.m33 = (((a.m13 * b.m31) + (a.m23 * b.m32)) + (a.m33 * b.m33)) + (a.m43 * b.m34);
		// result.m34 = (((a.m14 * b.m31) + (a.m24 * b.m32)) + (a.m34 * b.m33)) + (a.m44 * b.m34);
		// result.m41 = (((a.m11 * b.m41) + (a.m21 * b.m42)) + (a.m31 * b.m43)) + (a.m41 * b.m44);
		// result.m42 = (((a.m12 * b.m41) + (a.m22 * b.m42)) + (a.m32 * b.m43)) + (a.m42 * b.m44);
		// result.m43 = (((a.m13 * b.m41) + (a.m23 * b.m42)) + (a.m33 * b.m43)) + (a.m43 * b.m44);
		// result.m44 = (((a.m14 * b.m41) + (a.m24 * b.m42)) + (a.m34 * b.m43)) + (a.m44 * b.m44);
		result.m11 = (((a.m11 * b.m11) + (a.m21 * b.m12)) + (a.m31 * b.m13)) + (a.m41 * b.m14);
		result.m12 = (((a.m12 * b.m11) + (a.m22 * b.m12)) + (a.m32 * b.m13)) + (a.m42 * b.m14);
		result.m13 = (((a.m13 * b.m11) + (a.m23 * b.m12)) + (a.m33 * b.m13)) + (a.m43 * b.m14);
		result.m14 = (((a.m14 * b.m11) + (a.m24 * b.m12)) + (a.m34 * b.m13)) + (a.m44 * b.m14);
		result.m21 = (((a.m11 * b.m21) + (a.m21 * b.m22)) + (a.m31 * b.m23)) + (a.m41 * b.m24);
		result.m22 = (((a.m12 * b.m21) + (a.m22 * b.m22)) + (a.m32 * b.m23)) + (a.m42 * b.m24);
		result.m23 = (((a.m13 * b.m21) + (a.m23 * b.m22)) + (a.m33 * b.m23)) + (a.m43 * b.m24);
		result.m24 = (((a.m14 * b.m21) + (a.m24 * b.m22)) + (a.m34 * b.m23)) + (a.m44 * b.m24);
		result.m31 = (((a.m11 * b.m31) + (a.m21 * b.m32)) + (a.m31 * b.m33)) + (a.m41 * b.m34);
		result.m32 = (((a.m12 * b.m31) + (a.m22 * b.m32)) + (a.m32 * b.m33)) + (a.m42 * b.m34);
		result.m33 = (((a.m13 * b.m31) + (a.m23 * b.m32)) + (a.m33 * b.m33)) + (a.m43 * b.m34);
		result.m34 = (((a.m14 * b.m31) + (a.m24 * b.m32)) + (a.m34 * b.m33)) + (a.m44 * b.m34);
		result.m41 = (((a.m11 * b.m41) + (a.m21 * b.m42)) + (a.m31 * b.m43)) + (a.m41 * b.m44);
		result.m42 = (((a.m12 * b.m41) + (a.m22 * b.m42)) + (a.m32 * b.m43)) + (a.m42 * b.m44);
		result.m43 = (((a.m13 * b.m41) + (a.m23 * b.m42)) + (a.m33 * b.m43)) + (a.m43 * b.m44);
		result.m44 = (((a.m14 * b.m41) + (a.m24 * b.m42)) + (a.m34 * b.m43)) + (a.m44 * b.m44);

		return result;
	}
	Vector4 operator*(const Matrix4 &m, const Vector4 &b)
	{
		Vector4 v;
		v.x = dot_product_vec4(b, vec4(m.m11, m.m21, m.m31, m.m41));
		v.y = dot_product_vec4(b, vec4(m.m12, m.m22, m.m32, m.m42));
		v.z = dot_product_vec4(b, vec4(m.m13, m.m23, m.m33, m.m43));
		v.w = dot_product_vec4(b, vec4(m.m14, m.m24, m.m34, m.m44));
		return v;
	}
	// std::ostream& operator<<(std::ostream& os, const Matrix4 &matrix)
	// {
	// 	os << "\n" << "{ " << matrix.m11 << ", " << matrix.m21 << ", " << matrix.m31 << ", " << matrix.m41 << " }" << std::endl
	// 	<< "{ " << matrix.m12 << ", " << matrix.m22 << ", " << matrix.m32 << ", " << matrix.m42 << " }" << std::endl
	// 	<< "{ " << matrix.m13 << ", " << matrix.m23 << ", " << matrix.m33 << ", " << matrix.m43 << " }" << std::endl
	// 	<< "{ " << matrix.m14 << ", " << matrix.m24 << ", " << matrix.m34 << ", " << matrix.m44 << " }" << std::endl;

	// 	return os;
	// }
	std::ostream& operator<<(std::ostream& os, const Matrix4 &matrix)
	{
		os << "\n" << "{ " << matrix.m11 << ", " << matrix.m12 << ", " << matrix.m13 << ", " << matrix.m14 << " }" << std::endl
		<< "{ " << matrix.m21 << ", " << matrix.m22 << ", " << matrix.m23 << ", " << matrix.m24 << " }" << std::endl
		<< "{ " << matrix.m31 << ", " << matrix.m32 << ", " << matrix.m33 << ", " << matrix.m34 << " }" << std::endl
		<< "{ " << matrix.m41 << ", " << matrix.m42 << ", " << matrix.m43 << ", " << matrix.m44 << " }" << std::endl;

		return os;
	}

}