#pragma once

#include <iostream>
#include <string>
#include "GatsMath.h"

struct Material
{
	std::string name;
	float shininess;
	GatsMath::vec3 ambient;
	GatsMath::vec3 diffuse;
	GatsMath::vec3 specular;
	std::string diffuseTexture;
};
