#pragma once
#include <iostream>
#include <cmath>
#include "Vector.h"

namespace GatsMath
{
	template <typename T, int N, int M>
	class mat;


	typedef mat<float, 4, 4> mat4;

	// mat4x4 specialization
	template <typename T>
	class mat<T, 4, 4>
	{
	public:
		T data[4][4];

		mat()
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] = 0;
		}

		mat(T val)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] = static_cast<T>(0);
			data[0][0] = val;
			data[1][1] = val;
			data[2][2] = val;
			data[3][3] = val;
		}

		mat(vec4 v1, vec4 v2, vec4 v3, vec4 v4)
		{
			data[0][0] = v1.x; data[0][1] = v1.y; data[0][2] = v1.z; data[0][3] = v1.w;
			data[1][0] = v2.x; data[1][1] = v2.y; data[1][2] = v2.z; data[1][3] = v2.w;
			data[2][0] = v3.x; data[2][1] = v3.y; data[2][2] = v3.z; data[2][3] = v3.w;
			data[3][0] = v4.x; data[3][1] = v4.y; data[3][2] = v4.z; data[3][3] = v4.w;
		}

		mat(const mat<T, 4, 4>& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] = m.data[i][j];
		}

		mat<T, 4, 4>& operator=(const mat<T, 4, 4>& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] = m.data[i][j];
			return *this;
		}

		mat<T, 4, 4> operator+(const mat<T, 4, 4>& m) const
		{
			mat<T, 4, 4> result;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					result.data[i][j] = data[i][j] + m.data[i][j];
			return result;
		}

		mat<T, 4, 4> operator-(const mat<T, 4, 4>& m) const
		{
			mat<T, 4, 4> result;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					result.data[i][j] = data[i][j] - m.data[i][j];
			return result;
		}

		mat<T, 4, 4> operator*(const mat<T, 4, 4>& m) const
		{
			mat<T, 4, 4> result;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					for (int k = 0; k < 4; k++)
						result.data[i][j] += data[i][k] * m.data[k][j];
			return result;
		}

		vec4 operator*(const vec4& v) const
		{
			vec4 result;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					result.data[i] += data[i][j] * v.data[j];
			return result;
		}

		mat<T, 4, 4> operator*(T val) const
		{
			mat<T, 4, 4> result;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					result.data[i][j] = data[i][j] * val;
			return result;
		}

		mat<T, 4, 4> operator/(T val) const
		{
			mat<T, 4, 4> result;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					result.data[i][j] = data[i][j] / val;
			return result;
		}

		vec<T, 4>& operator[](int index)
		{
			if (index < 0 || index >= 4)
				throw std::out_of_range("Index out of range");
			vec<T, 4> v(data[index][0], data[index][1], data[index][2], data[index][3]);
			return v;
		}

		const vec<T, 4>& operator[](int index) const
		{
			if (index < 0 || index >= 4)
				throw std::out_of_range("Index out of range");
			vec<T, 4> v(data[index][0], data[index][1], data[index][2], data[index][3]);
			return v;
		}

		template <typename T>
		friend std::ostream& operator<<(std::ostream& os, const mat<T, 4, 4>& m)
		{
			for (int i = 0; i < 4; i++)
			{
				os << "[ ";
				for (int j = 0; j < 4; j++)
					os << m.data[i][j] << " ";
				os << "]\n";
			}
			return os;
		}
	};


	// mat4x4 functions
	template <typename T>
	T* value_ptr(mat<T, 4, 4>& m)
	{
		T* flatData = new T[16];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				flatData[i * 4 + j] = m.data[i][j];

		return flatData;
	}

	template <typename T>
	const T* value_ptr(const mat<T, 4, 4>& m)
	{
		return &m.data[0][0];
	}

	template <typename T>
	mat<T, 4, 4> transpose(const mat<T, 4, 4>& m)
	{
		mat<T, 4, 4> result;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.data[i][j] = m.data[j][i];

		return result;
	}

	template <typename T>
	T determinant3x3 (const T m[3][3])
	{
		return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
			+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	}

	template <typename T>
	mat<T, 4, 4> CofactorMatrix(const mat<T, 4, 4>& m)
	{
		mat<T, 4, 4> cofactors;

		for (int row = 0; row < 4; row++)
		{ 
			for (int col = 0; col < 4; col++)
			{
				T subMatrix[3][3];
				int subRow = 0, subCol = 0;
				for (int k = 0; k < 4; k++)
					for (int l = 0; l < 4; l++)
						if (k != row && l != col)
						{
							subMatrix[subRow][subCol] = m.data[k][l];
							subCol++;
							if (subCol == 3)
							{
								subCol = 0;
								subRow++;
							}
						}
				T cofactor = ((row + col) % 2 == 0 ? 1 : -1) * determinant3x3(subMatrix);
				cofactors.data[row][col] = cofactor;
			}
		}
		return cofactors;
	}

	template <typename T>
	T determinant4x4(const mat<T, 4, 4>& m)
	{
		return (m.data[0][0] * m.data[1][1] * m.data[2][2] * m.data[3][3] // 00 11 22 33
				+ m.data[0][0] * m.data[1][2] * m.data[2][3] * m.data[3][1] // 00 12 23 31
				+ m.data[0][0] * m.data[1][3] * m.data[2][1] * m.data[3][2] // 00 13 21 32
				+ m.data[0][1] * m.data[1][0] * m.data[2][3] * m.data[3][2] // 01 10 23 32
				+ m.data[0][1] * m.data[1][2] * m.data[2][0] * m.data[3][3] // 01 12 20 33
				+ m.data[0][1] * m.data[1][3] * m.data[2][2] * m.data[3][0] // 01 13 22 30
				+ m.data[0][2] * m.data[1][0] * m.data[2][1] * m.data[3][3] // 02 10 21 33
				+ m.data[0][2] * m.data[1][1] * m.data[2][3] * m.data[3][0] // 02 11 23 30
				+ m.data[0][2] * m.data[1][3] * m.data[2][0] * m.data[3][1] // 02 13 20 31
				+ m.data[0][3] * m.data[1][0] * m.data[2][2] * m.data[3][1] // 03 10 22 31
				+ m.data[0][3] * m.data[1][1] * m.data[2][0] * m.data[3][2] // 03 11 20 32
				+ m.data[0][3] * m.data[1][2] * m.data[2][1] * m.data[3][0] // 03 12 21 30)
			- (m.data[0][0] * m.data[1][1] * m.data[2][3] * m.data[3][2] // 00 11 23 32
				+ m.data[0][0] * m.data[1][2] * m.data[2][1] * m.data[3][3] // 00 12 21 33
				+ m.data[0][0] * m.data[1][3] * m.data[2][2] * m.data[3][1] // 00 13 22 31
				+ m.data[0][1] * m.data[1][0] * m.data[2][2] * m.data[3][3] // 01 10 22 33
				+ m.data[0][1] * m.data[1][2] * m.data[2][3] * m.data[3][0] // 01 12 23 30
				+ m.data[0][1] * m.data[1][3] * m.data[2][0] * m.data[3][2] // 01 13 20 32
				+ m.data[0][2] * m.data[1][0] * m.data[2][3] * m.data[3][1] // 02 10 23 31
				+ m.data[0][2] * m.data[1][1] * m.data[2][0] * m.data[3][3] // 02 11 20 33
				+ m.data[0][2] * m.data[1][3] * m.data[2][1] * m.data[3][0] // 02 13 21 30
				+ m.data[0][3] * m.data[1][0] * m.data[2][1] * m.data[3][2] // 03 10 21 32
				+ m.data[0][3] * m.data[1][1] * m.data[2][2] * m.data[3][0] // 03 11 22 30
				+ m.data[0][3] * m.data[1][2] * m.data[2][0] * m.data[3][1])); // 03 12 20 31
	}

	template <typename T>
	mat<T, 4, 4> inverse(const mat<T, 4, 4>& m)
	{
		T det = determinant4x4(m);
		if (det == 0)
			throw std::runtime_error("Matrix is not invertible");

		mat<T, 4, 4> cofactors = CofactorMatrix(m);

		mat<T, 4, 4> adjugate = transpose<T>(cofactors);

		mat<T, 4, 4> inv;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				inv.data[i][j] = adjugate.data[i][j] / det;

		return inv;
	}


	template <typename T>
	mat<T, 4, 4> translate(const mat<T, 4, 4>& m, const vec3& v)
	{
		mat<T, 4, 4> result = mat<T, 4, 4>(vec4(1, 0, 0, v.x),
											vec4(0, 1, 0, v.y),
											vec4(0, 0, 1, v.z),
											vec4(0, 0, 0, 1));

		mat <T, 4, 4> res = result * m;

		return res;
	}

	template <typename T>
	mat<T, 4, 4> scale(const mat<T, 4, 4>& m, const vec3& v)
	{
		mat<T, 4, 4> result = mat<T, 4, 4>(vec4(v.x, 0, 0, 0),
											vec4(0, v.y, 0, 0),
											vec4(0, 0, v.z, 0),
											vec4(0, 0, 0, 1));

		mat <T, 4, 4> res = result * m;
		return res;
	}

	template <typename T>
	mat<T, 4, 4> rotate(const mat<T, 4, 4>& m, T angle, const vec3& v)
	{
		vec3 nv = v.normalize();

		if (nv == vec3(1, 0, 0))
		{
			mat<T, 4, 4> result = mat<T, 4, 4>(vec4(1,	0,			0,				0),
												vec4(0, cos(angle), -sin(angle),	0),
												vec4(0, sin(angle), cos(angle),		0),
												vec4(0, 0,			0,				1));

			mat<T, 4, 4> res = result * m;

			return res;
		}
		else if (nv == vec3(0, 1, 0))
		{
			mat<T, 4, 4> result = mat<T, 4, 4>(vec4(cos(angle), 0, sin(angle),	0),
												vec4(0,			1,		0,		0),
												vec4(-sin(angle), 0, cos(angle), 0),
												vec4(0,			0,		0,		1));

			mat<T, 4, 4> res = result * m;
			return res;
		}
		else if (nv == vec3(0, 0, 1))
		{
			mat<T, 4, 4> result = mat<T, 4, 4>(vec4(cos(angle),		-sin(angle),	0,		0),
												vec4(sin(angle),	cos(angle),		0,		0),
												vec4(0,				0,				1,		0),
												vec4(0,				0,				0,		1));

			mat<T, 4, 4> res = result * m;

			return res;
		}
		else
		{
			T c = cos(angle);
			T s = sin(angle);
			T t = 1.0f - c;
			T x = v.x;
			T y = v.y;
			T z = v.z;

			mat<T, 4, 4> result = mat<T, 4, 4>( vec4((t * x * x) + c,		t * x * y - s * z,	t * x * z + s * y,	0),
												vec4(t * x * y + s * z, t * y * y + c,		t * y * z - s * x,	0),
												vec4(t * x * z - s * y, t * y * z + s * x,	t * z * z + c,		0),
												vec4(0,					0,					0,					1));

			mat<T,4,4> res = result * m;

			return res;
		}
	}

	template <typename T>
	mat<T, 4, 4> perspective(T fov, T aspect, T zNear, T zFar)
	{
		mat<T, 4, 4> result;

		T const tanHalFovy = std::tan(fov / static_cast<T>(2));

		result = mat<T, 4, 4>(vec4(static_cast<T>(1) / (aspect * tanHalFovy),			0,								0,			0),
								vec4(0,											static_cast<T>(1) / tanHalFovy,		0,			0),
								vec4(0,											0,								-(zFar + zNear) / (zFar - zNear),		-static_cast<T>(1)),
								vec4(0,											0,								-((static_cast<T>(2) * zFar * zNear) / (zFar - zNear)), 0));

		return result;
	}

	template <typename T>
	mat<T, 4, 4> orthographic(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		mat<T, 4, 4> result;

		result = mat<T, 4, 4>(vec4(2 / (right - left), 0, 0, -((right + left)/(right - left))),
							vec4(0, 2 / (top - bottom), 0, -((top + bottom)/(top - bottom))),
							vec4(0, 0, 2 / (zNear - zFar), -((zFar + zNear)/(zFar - zNear))),
							vec4(0, 0, 0, 1));

		return result;
	}

	template <typename T>
	mat<T, 4, 4> lookAt(const vec<float, 3>& eye, const vec<float, 3>& target, const vec<float, 3>& up)
	{
		vec3 cameraZ = (target - eye).normalize();
		vec3 cameraX = cross(up, cameraZ).normalize();
		vec3 cameraY = cross(cameraZ, cameraX);

		mat<T, 4, 4> result = mat<T, 4, 4>(vec4(cameraX.x, cameraY.x, -cameraZ.x, 0),
											vec4(cameraX.y, cameraY.y, -cameraZ.y, 0),
											vec4(cameraX.z, cameraY.z, -cameraZ.z, 0),
											vec4(-dot(cameraX, eye), -dot(cameraY, eye), dot(cameraZ, eye), 1));
		return result;
	}

	// General template
	template <typename T, int N, int M>
	class mat
	{};
}