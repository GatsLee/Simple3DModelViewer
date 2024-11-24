#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

class Model
{
public:
	Model(const std::string& objFileLocation, const std::string& mtlFileLocation,
		const std::vector<std::string> &textureFileLocations, Shader *shaderToAdjust);
	~Model();

	bool isModelLoaded() const;

	void CreateModel();
	void RenderModel();
	void ClearModel();

private:
	Mesh* meshProp;
	std::unordered_map<std::string, Texture *> textures;
	std::unordered_map<std::string, GLuint> textureUnits;
	std::unordered_map<std::string, Material *> materials;
	std::vector<std::string> textureFileLocations;
	std::string mtlFileLocation;
	Shader* shader;

	bool isMeshLoaded;
	bool isMtlLoaded;
	bool areTexturesLoaded;

	bool LoadMTLFile();
};

