#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GatsMath.h"
#include "Texture.h"
#include "Material.h"

struct Vertex {
	float x, y, z;
};

struct TextureCoord {
	float u, v;
};

struct Normal {
	float nx, ny, nz;
};

struct Face {
	std::string activeMaterial;         // Active material
	std::vector<int> vertexIndices;     // Indices for vertices
	std::vector<int> textureIndices;    // Indices for texture coordinates
	std::vector<int> normalIndices;     // Indices for normals
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool LoadObj(const std::string& fileName);
	//bool CreateCustomModel(GLfloat* vertices, unsigned int* indices,
	//	unsigned int numOfVertices, unsigned int numOfIndices);

	void CreateMesh(const std::unordered_map<std::string, Texture*>& textures, 
						const std::unordered_map<std::string, struct Material*>& materials);
	void RenderMesh(const std::unordered_map<std::string, Texture*>& textures, 
						const std::unordered_map<std::string, struct Material*>& materials);
	void ClearMesh();

private:

	std::vector<Vertex> vertices;
	std::vector<TextureCoord> uvs;
	std::vector<Normal> normals;
	std::vector<Face> faces;

	std::unordered_map<std::string, GLfloat> materialVAOs;
	std::unordered_map<std::string, GLfloat> materialVBOs;
	std::unordered_map<std::string, GLfloat> materialIBOs;
	std::unordered_map<std::string, GLsizei> materialIndexCounts;

	void CalculateAverageNormals(unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount, 
								unsigned int vLength, unsigned int uvLength, unsigned int normalLength);

	std::vector<std::string> SplitObjLine(const std::string& s, char delimiter);
};
