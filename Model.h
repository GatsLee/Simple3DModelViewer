#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

class Model
{
public:
	Model(const std::string& objFileLocation, const std::string& mtlFileLocation,
		const std::vector<std::string> &textureFileLocations);
	~Model();

	bool isModelLoaded() const;

	void CreateModel();
	void RenderModel();
	void ClearModel();

private:
	Mesh* meshProp;
	std::unordered_map<std::string, Texture *> textures;
	std::unordered_map<std::string, Material *> materials;
	std::vector<std::string> textureFileLocations;
	std::string mtlFileLocation;

	bool isMeshLoaded;
	bool isMtlLoaded;
	bool areTexturesLoaded;

	bool LoadMTLFile();
};

