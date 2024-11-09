#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T, std::size_t N>
class vec
{
public:
	std::vector<T> data(N);

	vec()
	{
		for (auto& i : data)
		{
			i = 0;
		}
	}

	vec(std::initializer_list<T> list)
	{
		int i = 0;
		for (auto& item : list)
		{
			data[i] = item;
			i++;
		}
	}

	vec<T, N> operator+(const vec<T, N>& other)
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] + other.data[i];
		}
		return result;
	}

	vec<T, N> operator-(const vec<T, N>& other)
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] - other.data[i];
		}
		return result;
	}

	vec<T, N> operator*(const vec<T, N>& other)
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] * other.data[i];
		}
		return result;
	}

	vec<T, N> operator/(const vec<T, N>& other)
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] / other.data[i];
		}
		return result;
	}

	vec<T, N> operator+=(const vec<T, N>& other)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] += other.data[i];
		}
		return *this;
	}

	vec<T, N> operator-=(const vec<T, N>& other)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] -= other.data[i];
		}
		return *this;
	}

	vec<T, N> operator*=(const vec<T, N>& other)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] *= other.data[i];
		}
		return *this;
	}

	vec<T, N> operator/=(const vec<T, N>& other)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] /= other.data[i];
		}
		return *this;
	}

	vec<T, N> operator+(const T& other) // scalar addition
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] + other;
		}
		return result;
	}

	vec<T, N> operator-(const T& other) // scalar subtraction
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] - other;
		}
		return result;
	}

	vec<T, N> operator*(const T& other) // scalar multiplication
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] * other;
		}
		return result;
	}

	vec<T, N> operator/(const T& other) // scalar division
	{
		vec<T, N> result;
		for (int i = 0; i < N; i++)
		{
			result.data[i] = data[i] / other;
		}
		return result;
	}

	vec<T, N> operator+=(const T& other) // scalar addition
	{
		for (int i = 0; i < N; i++)
		{
			data[i] += other;
		}
		return *this;
	}

};
