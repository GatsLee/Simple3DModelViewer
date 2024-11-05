#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.h"

namespace GatsMath
{
	inline float ToRadians(float degrees) { return degrees * (3.14159265359f / 180.0f); }
}