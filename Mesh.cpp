#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

Mesh::~Mesh()
{
}

bool Mesh::LoadModel(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Error: Could not open file " << fileName << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string lineType;
		ss >> lineType;

		if (lineType == "v")
		{
			struct Vertex vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (lineType == "vt")
		{
			struct TextureCoord uv;
			ss >> uv.u >> uv.v;
			uvs.push_back(uv);
		}
		else if (lineType == "vn")
		{
			struct Normal normal;
			ss >> normal.nx >> normal.ny >> normal.nz;
			normals.push_back(normal);
		}
		else if (lineType == "f")
		{
			struct Face face;
			int vertexIndex[3], uvIndex[3], normalIndex[3];
			char slash;

			for (int i = 0; i < 3; i++)
			{
				ss >> vertexIndex[i] >> slash >> uvIndex[i] >> slash >> normalIndex[i];
				face.vertexIndices.push_back(vertexIndex[i]);
				face.textureIndices.push_back(uvIndex[i]);
				face.normalIndices.push_back(normalIndex[i]);
				faces.push_back(face);
			}
		}
	}
	return true;
}

void Mesh::CreateMesh()
{
	std::vector<float> interleavedVertices;
	std::vector<unsigned int> indices;

	for (const Face& face : faces)
	{
		for (size_t i = 0; i < face.vertexIndices.size(); ++i)
		{
			int vIdx = face.vertexIndices[i] - 1;
			interleavedVertices.push_back(vertices[vIdx].x);
			interleavedVertices.push_back(vertices[vIdx].y);
			interleavedVertices.push_back(vertices[vIdx].z);

			if (face.textureIndices.size() > i) {
				int uvIdx = face.textureIndices[i] - 1;
				interleavedVertices.push_back(uvs[uvIdx].u);
				interleavedVertices.push_back(uvs[uvIdx].v);
			}
			else {
				interleavedVertices.push_back(0.0f);
				interleavedVertices.push_back(0.0f);
			}

			if (face.normalIndices.size() > i) {
				int nIdx = face.normalIndices[i] - 1;
				interleavedVertices.push_back(normals[nIdx].nx);
				interleavedVertices.push_back(normals[nIdx].ny);
				interleavedVertices.push_back(normals[nIdx].nz);
			}
			else {
				interleavedVertices.push_back(0.0f);
				interleavedVertices.push_back(0.0f);
				interleavedVertices.push_back(0.0f);
			}

			indices.push_back(indices.size());
		}
	}
	indexCount = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * sizeof(GLfloat), &interleavedVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0);
	glEnableVertexAttribArray(0);

	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	// Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
	vertices.clear();
	uvs.clear();
	normals.clear();
	faces.clear();
}

void Mesh::CalculateAverageNormals(unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount, unsigned int vLength, unsigned int uvLength, unsigned int normalLength)
{
}
