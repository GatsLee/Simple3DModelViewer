#include "Model.h"

Model::Model(const std::string& objFileLoc, const std::string& mtlFileLoc, 
				const std::vector<std::string>& textureFileLocs, Shader *shaderToAdjust)
	: shader(shaderToAdjust)
{
	// Load the Mesh
	meshProp = new Mesh();
	if (meshProp->LoadObj(objFileLoc))
	{
		isMeshLoaded = true;
	}
	else
	{
		isMeshLoaded = false;
	}

	mtlFileLocation = mtlFileLoc;
	// Load the Material
	if (LoadMTLFile())
	{
		isMtlLoaded = true;
	}
	else
	{
		isMtlLoaded = false;
	}

	textureFileLocations = textureFileLocs;
	areTexturesLoaded = true;
	int textureUnit = 1;
	// Load the Textures
	for (auto textureFile : textureFileLocations)
	{
		Texture *texture = new Texture(textureFile, "bmp");
		if (texture->LoadTexture())
		{
			textures[textureFile] = texture;
			textures[textureFile]->UseTexture(GL_TEXTURE0 + textureUnit);
			textureUnits[texture->GetFileName()] = textureUnit;
			textureUnit++;
		}
		else
		{
			delete texture;
			areTexturesLoaded = false;
			break;
		}
	}
}

Model::~Model()
{
}

bool Model::isModelLoaded() const
{
	if (isMeshLoaded && isMtlLoaded && areTexturesLoaded)
	{
		return true;
	}
	else
	{
		if (!isMeshLoaded)
		{
			std::cout << "Mesh not loaded" << std::endl;
		}

		if (!isMtlLoaded)
		{
			std::cout << "Material not loaded" << std::endl;
		}

		if (!areTexturesLoaded)
		{
			std::cout << "Textures not loaded" << std::endl;
		}
		return false;
	}
}

void Model::CreateModel()
{
	meshProp->CreateMesh(textures, textureUnits, materials);
}

void Model::RenderModel()
{
	meshProp->RenderMesh(textures, textureUnits, materials, shader);
}

void Model::ClearModel()
{
	meshProp->ClearMesh();
	for (auto texture : textures)
	{
		delete texture.second;
	}
	textures.clear();
	materials.clear();
}

bool Model::LoadMTLFile()
{
	std::ifstream file(mtlFileLocation);
	Material *material = new Material();

	if (!file.is_open())
	{
		std::cout << "Error: Could not open file " << mtlFileLocation << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string lineType;
		ss >> lineType;

		if (lineType == "newmtl")
		{

			if (material->name != "")
			{
				materials[material->name] = material;
			}
			material = new Material();
			ss >> material->name;
		}
		else if (lineType == "Ns")
		{
			ss >> material->shininess;
		}
		else if (lineType == "Ka")
		{
			ss >> material->ambient.x >> material->ambient.y >> material->ambient.z;
		}
		else if (lineType == "Kd")
		{
			ss >> material->diffuse.x >> material->diffuse.y >> material->diffuse.z;
		}
		else if (lineType == "Ks")
		{
			ss >> material->specular.x >> material->specular.y >> material->specular.z;
		}
		else if (lineType == "map_Kd")
		{
			ss >> material->diffuseTexture;
		}
	}

	if (material->name != "")
	{
		materials[material->name] = material;
	}
	file.close();
	return true;
}
