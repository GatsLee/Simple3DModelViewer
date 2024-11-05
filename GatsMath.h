#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"

namespace GatsMath
{
	float toRadians(float degrees) { return degrees * (3.14159265359f / 180.0f); }
	float cos(float radians) { return std::cos(radians); }
	float sin(float radians) { return std::sin(radians); }
	float tan(float radians) { return std::tan(radians); }

	float acos(float radians) { return std::acos(radians); }
	float asin(float radians) { return std::asin(radians); }
	float atan(float radians) { return std::atan(radians); }

	float sqrt(float val) { return std::sqrt(val); }
	float pow(float base, float exponent) { return std::pow(base, exponent); }
	float abs(float val) { return std::abs(val); }
	float floor(float val) { return std::floor(val); }
	float ceil(float val) { return std::ceil(val); }
	float round(float val) { return std::round(val); }
	float mod(float val, float divisor) { return std::fmod(val, divisor); }
	float max(float val1, float val2) { return std::max(val1, val2); }
	float min(float val1, float val2) { return std::min(val1, val2); }
}