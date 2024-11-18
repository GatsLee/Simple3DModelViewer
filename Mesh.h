#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GatsMath.h"

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
	std::vector<int> vertexIndices;     // Indices for vertices
	std::vector<int> textureIndices;    // Indices for texture coordinates
	std::vector<int> normalIndices;     // Indices for normals
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool LoadModel(const std::string& fileName);
	bool CreateCustomModel(GLfloat* vertices, unsigned int* indices,
		unsigned int numOfVertices, unsigned int numOfIndices);

	void CreateMesh();
	void RenderMesh();
	void ClearMesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

	std::vector<Vertex> vertices;
	std::vector<TextureCoord> uvs;
	std::vector<Normal> normals;
	std::vector<Face> faces;

	void CalculateAverageNormals(unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount, 
								unsigned int vLength, unsigned int uvLength, unsigned int normalLength);

	std::vector<std::string> SplitObjLine(const std::string& s, char delimiter);
};
