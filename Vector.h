#pragma once

#include <iostream>
#include <cmath>
#include "GL/glew.h"

namespace GatsMath
{
	template <typename T, int N>
	class vec; // Forward declare general template

	typedef vec<float, 2> vec2;
	typedef vec<float, 3> vec3;
	typedef vec<float, 4> vec4;

	// Specialization for vec<T, 2>
	template <typename T>
	class vec<T, 2>
	{
	public:
		union {
			T data[2];
			struct { T x, y; };
		};

		vec() : x(0), y(0) {}

		vec(T val) : x(val), y(val) {}

		vec(T x, T y) : x(x), y(y) {}

		vec(const vec<T, 2>& v)
		{
			x = v.x;
			y = v.y;
		}

		vec(T* arr)
		{
			x = arr[0];
			y = arr[1];
		}

		~vec() {}

		T operator[](int index) const
		{
			if (index < 0 || index >= 2)
				throw std::out_of_range("Index out of range");
			return data[index];
		}

		vec<T, 2> operator+(const vec<T, 2>& v) const
		{
			vec<T, 2> result;
			result.x = x + v.x;
			result.y = y + v.y;
			return result;
		}

		vec<T, 2> operator-(const vec<T, 2>& v) const
		{
			vec<T, 2> result;
			result.x = x - v.x;
			result.y = y - v.y;
			return result;
		}

		vec<T, 2> operator*(const vec<T, 2>& v) const
		{
			vec<T, 2> result;
			result.x = x * v.x;
			result.y = y * v.y;
			return result;
		}

		vec<T, 2> operator/(const vec<T, 2>& v) const
		{
			vec<T, 2> result;
			result.x = x / v.x;
			result.y = y / v.y;
			return result;
		}

		vec<T, 2> operator+(T val) const
		{
			vec<T, 2> result;
			result.x = x + val;
			result.y = y + val;
			return result;
		}

		vec<T, 2> operator-(T val) const
		{
			vec<T, 2> result;
			result.x = x - val;
			result.y = y - val;
			return result;
		}

		vec<T, 2> operator*(T val) const
		{
			vec<T, 2> result;
			result.x = x * val;
			result.y = y * val;
			return result;
		}

		vec<T, 2> operator/(T val) const
		{
			vec<T, 2> result;
			result.x = x / val;
			result.y = y / val;
			return result;
		}

		vec<T, 2> normalize() const
		{
			vec<T, 2> result;
			T length = sqrt(x * x + y * y);
			result.x = x / length;
			result.y = y / length;
			return result;
		}
	};

	// vec<T, 2> functions
	template <typename T>
	float* value_ptr(const vec<T, 2>& v)
	{
		return &v.x;
	}

	template <typename T>
	float dot(const vec<T, 2>& v1, const vec<T, 2>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <typename T>
	vec<T, 2> cross(const vec<T, 2>& v1, const vec<T, 2>& v2)
	{
		vec<T, 2> result;
		result.x = v1.x * v2.y - v1.y * v2.x;
		result.y = v1.y * v2.x - v1.x * v2.y;
		return result;
	}

	// Specialization for vec<T, 3>
	template <typename T>
	class vec<T, 3> {
	public:
		union {
			T data[3];
			struct { T x, y, z; };
		};

		vec() : x(0), y(0), z(0) {}

		vec(T val) : x(val), y(val), z(val) {}

		vec(T x, T y, T z) : x(x), y(y), z(z) {}

		vec(const vec<T, 3>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		vec(T* arr)
		{
			x = arr[0];
			y = arr[1];
			z = arr[2];
		}

		T operator[](int index) const
		{
			if (index < 0 || index >= 3)
				throw std::out_of_range("Index out of range");
			return data[index];
		}

		vec<T, 3> operator+(const vec<T, 3>& v) const
		{
			vec<T, 3> result;
			result.x = x + v.x;
			result.y = y + v.y;
			result.z = z + v.z;
			return result;
		}

		vec<T, 3> operator-(const vec<T, 3>& v) const
		{
			vec<T, 3> result;
			result.x = x - v.x;
			result.y = y - v.y;
			result.z = z - v.z;
			return result;
		}

		vec<T, 3> operator*(const vec<T, 3>& v) const
		{
			vec<T, 3> result;
			result.x = x * v.x;
			result.y = y * v.y;
			result.z = z * v.z;
			return result;
		}

		vec<T, 3> operator/(const vec<T, 3>& v) const
		{
			vec<T, 3> result;
			result.x = x / v.x;
			result.y = y / v.y;
			result.z = z / v.z;
			return result;
		}

		vec<T, 3> operator+(T val) const
		{
			vec<T, 3> result;
			result.x = x + val;
			result.y = y + val;
			result.z = z + val;
			return result;
		}

		vec<T, 3> operator-(T val) const
		{
			vec<T, 3> result;
			result.x = x - val;
			result.y = y - val;
			result.z = z - val;
			return result;
		}

		vec<T, 3> operator*(T val) const
		{
			vec<T, 3> result;
			result.x = x * val;
			result.y = y * val;
			result.z = z * val;
			return result;
		}

		vec<T, 3> operator/(T val) const
		{
			vec<T, 3> result;
			result.x = x / val;
			result.y = y / val;
			result.z = z / val;
			return result;
		}

		bool operator==(const vec<T, 3>& v) const
		{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const vec<T, 3>& v) const
		{
			return x != v.x || y != v.y || z != v.z;
		}

		vec<T, 3> normalize() const
		{
			vec<T, 3> result;
			T length = std::sqrt(x * x + y * y + z * z);
			result.x = x / length;
			result.y = y / length;
			result.z = z / length;
			return result;
		}

		float* value_ptr()
		{
			return &x;
		}
	};


	// vec<T, 3> functions
	template<typename T>
	float* value_ptr(const vec<T, 3>& v)
	{
		return &v.x;
	}

	template <typename T>
	float dot(const vec<T, 3>& v1, const vec<T, 3>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template <typename T>
	vec<float, 3> cross(const vec<T, 3>& v1, const vec<T, 3>& v2)
	{
		vec<float, 3> result;
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;
		return result;
	}

	// Specialization for vec<T, 4>
	template <typename T>
	class vec<T, 4> {
	public:
		union {
			T data[4];
			struct { T x, y, z, w; };
		};

		vec() : x(0), y(0), z(0), w(0) {}

		vec(T val) : x(val), y(val), z(val), w(val) {}

		vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		T operator[](int index) const
		{
			if (index < 0 || index >= 4)
				throw std::out_of_range("Index out of range");
			return data[index];
		}

		vec(const vec<T, 4>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}

		vec(T* arr)
		{
			x = arr[0];
			y = arr[1];
			z = arr[2];
			w = arr[3];
		}

		vec<T, 4> operator+(const vec<T, 4>& v) const
		{
			vec<T, 4> result;
			result.x = x + v.x;
			result.y = y + v.y;
			result.z = z + v.z;
			result.w = w + v.w;
			return result;
		}

		vec<T, 4> operator-(const vec<T, 4>& v) const
		{
			vec<T, 4> result;
			result.x = x - v.x;
			result.y = y - v.y;
			result.z = z - v.z;
			result.w = w - v.w;
			return result;
		}

		vec<T, 4> operator*(const vec<T, 4>& v) const
		{
			vec<T, 4> result;
			result.x = x * v.x;
			result.y = y * v.y;
			result.z = z * v.z;
			result.w = w * v.w;
			return result;
		}

		vec<T, 4> operator/(const vec<T, 4>& v) const
		{
			vec<T, 4> result;
			result.x = x / v.x;
			result.y = y / v.y;
			result.z = z / v.z;
			result.w = w / v.w;
			return result;
		}

		vec<T, 4> operator+(T val) const
		{
			vec<T, 4> result;
			result.x = x + val;
			result.y = y + val;
			result.z = z + val;
			result.w = w + val;
			return result;
		}

		vec<T, 4> operator-(T val) const
		{
			vec<T, 4> result;
			result.x = x - val;
			result.y = y - val;
			result.z = z - val;
			result.w = w - val;
			return result;
		}

		vec<T, 4> operator*(T val) const
		{
			vec<T, 4> result;
			result.x = x * val;
			result.y = y * val;
			result.z = z * val;
			result.w = w * val;
			return result;
		}

		vec<T, 4> operator/(T val) const
		{
			vec<T, 4> result;
			result.x = x / val;
			result.y = y / val;
			result.z = z / val;
			result.w = w / val;
			return result;
		}

		vec<T, 4> normalize() const
		{
			vec<T, 4> result;
			T length = sqrt(x * x + y * y + z * z + w * w);
			result.x = x / length;
			result.y = y / length;
			result.z = z / length;
			result.w = w / length;
			return result;
		}
	};

	// vec<T, 4> functions
	template<typename T>
	float* value_ptr(const vec<T, 4>& v)
	{
		return &v.x;
	}

	template <typename T>
	float dot(const vec<T, 4>& v1, const vec<T, 4>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template <typename T>
	vec<float, 4> cross(const vec<T, 4>& v1, const vec<T, 4>& v2)
	{
		vec<float, 4> result;
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;
		return result;
	}

	// General vec<T, N> functions
	template <typename T, int N>
	float length(const vec<T, N>& v)
	{
		float result = 0;
		for (int i = 0; i < N; i++)
		{
			result += v.data[i] * v.data[i];
		}
		return sqrt(result);
	}

	// General vec<T, N> class
	template <typename T, int N>
	class vec
	{};
}