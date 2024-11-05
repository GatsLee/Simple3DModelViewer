#pragma once

#include <iostream>
#include <type_traits>
#include "GL/glew.h"

namespace GatsMath
{
	template <typename T, std::size_t N>
	class vec
	{
	public:
		T data[N];

		vec() { for (int i = 0; i < N; i++) data[i] = 0; }
		vec(T val) { for (int i = 0; i < N; i++) data[i] = val; }
		template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
		vec(Args... args) : data{ args... } {}
		vec(const vec<T, N>& v) { for (int i = 0; i < N; i++) data[i] = v.data[i]; }
		vec(T* arr) { for (int i = 0; i < N; i++) data[i] = arr[i]; }
		~vec() {}

		vec<T, N> operator+(const vec<T, N>& v) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] + v.data[i];
			return result;
		}

		vec<T, N> operator-(const vec<T, N>& v) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] - v.data[i];
			return result;
		}

		vec<T, N> operator*(const vec<T, N>& v) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] * v.data[i];
			return result;
		}

		vec<T, N> operator/(const vec<T, N>& v) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] / v.data[i];
			return result;
		}

		vec<T, N> operator+(T val) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] + val;
			return result;
		}

		vec<T, N> operator-(T val) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] - val;
			return result;
		}

		vec<T, N> operator*(T val) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] * val;
			return result;
		}

		vec<T, N> operator/(T val) const
		{
			vec<T, N> result;
			for (int i = 0; i < N; i++) result.data[i] = data[i] / val;
			return result;
		}

		vec<T, N>& operator=(const vec<T, N>& v)
		{
			for (int i = 0; i < N; i++) data[i] = v.data[i];
			return *this;
		}

		vec<T, N>& operator+=(const vec<T, N>& v)
		{
			for (int i = 0; i < N; i++) data[i] += v.data[i];
			return *this;
		}

		vec<T, N>& operator-=(const vec<T, N>& v)
		{
			for (int i = 0; i < N; i++) data[i] -= v.data[i];
			return *this;
		}

		vec<T, N>& operator*=(const vec<T, N>& v)
		{
			for (int i = 0; i < N; i++) data[i] *= v.data[i];
			return *this;
		}

		vec<T, N>& operator/=(const vec<T, N>& v)
		{
			for (int i = 0; i < N; i++) data[i] /= v.data[i];
			return *this;
		}

		vec<T, N>& operator+=(T val)
		{
			for (int i = 0; i < N; i++) data[i] += val;
			return *this;
		}

		vec<T, N>& operator-=(T val)
		{
			for (int i = 0; i < N; i++) data[i] -= val;
			return *this;
		}

		vec<T, N>& operator*=(T val)
		{
			for (int i = 0; i < N; i++) data[i] *= val;
			return *this;
		}

		vec<T, N>& operator/=(T val)
		{
			for (int i = 0; i < N; i++) data[i] /= val;
			return *this;
		}

		T& operator[](int i) { return data[i]; }

		const T& operator[](int i) const { return data[i]; }

		T dot(const vec<T, N>& v) const
		{
			T result = 0;
			for (int i = 0; i < N; i++) result += data[i] * v.data[i];
			return result;
		}

		GLfloat length() const
		{
			GLfloat result = 0;
			for (int i = 0; i < N; i++) result += data[i] * data[i];
			return std::sqrt(result);
		}

	};

	class vec2 : public vec<float, 2> {
	public:
		union {
			struct {
				float x;
				float y;
			};
			float data[2];
		};

		vec2() : vec<float, 2>() {}
		vec2(float x, float y) : vec<float, 2>(x, y),
			x(this->data[0]), y(this->data[1]) {}
	};

	class vec3 : public vec<float, 3> {
	public:
		float x;
		float y;
		float z;

		vec3() : vec<float, 3>(), 
			x(this->data[0]), y(this->data[1]), z(this->data[2]) {}
		vec3(float x, float y, float z) : vec<float, 3>(x, y, z),
			x(this->data[0]), y(this->data[1]), z(this->data[2]) {}
	};

	template <typename T>
	class vec4 : public vec<T, 4> {
	public:
		//float& x = this->data[0];
		//float& y = this->data[1];
		//float& z = this->data[2];
		//float& w = this->data[3];

		vec4() : vec<T, 4>() {}
		vec4(T x, T y, T z, T w) : vec<T, 4>(x, y, z, w) {}
	};
}