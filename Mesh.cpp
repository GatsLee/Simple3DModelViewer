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

std::vector<std::string> Mesh::SplitObjLine(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens(5, "");
	int tokenIdx = 0;
	std::string token;

	for (char c : s)
	{

		if (c == delimiter)
		{
			tokens[tokenIdx] = token;
			token = "";
			tokenIdx++;
		}
		else
		{
			token += c;
		}
	}
	tokens[tokenIdx] = token;
	return tokens;
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
			int vertexIndex[4], uvIndex[4], normalIndex[4];
			char slash;

			// check if face is a quad or triangle
			int numVertices = 0;
			std::string temp;
			std::istringstream ss2(line);
			while (ss2 >> temp)
			{
				numVertices++;
			}

			ss.clear();
			ss.seekg(0, std::ios::beg);

			if (numVertices == 5) // 4 vertices
			{
				std::vector<std::string> chunks = SplitObjLine(line, ' ');
				// Triangulate quad
				for (int i = 0; i < 4; i++) // 4 vertices per face
				{
					vertexIndex[i] = uvIndex[i] = normalIndex[i] = 0;

					// v/t/n : some elements may be missing
					std::vector<std::string> tokens = SplitObjLine(chunks[i+1], '/');
					vertexIndex[i] = (tokens[0] == "" ? 0 : std::stoi(tokens[0], nullptr));
					uvIndex[i] = (tokens[1] == "" ? 0 : std::stoi(tokens[1], nullptr));
					normalIndex[i] = (tokens[2] == "" ? 0 : std::stoi(tokens[2], nullptr));
					face.vertexIndices.push_back(vertexIndex[i]);
					face.textureIndices.push_back(uvIndex[i]);
					face.normalIndices.push_back(normalIndex[i]);
				}

				// Triangulate quad
				struct Face face2;
				face2.vertexIndices.push_back(face.vertexIndices[0]);
				face2.vertexIndices.push_back(face.vertexIndices[2]);
				face2.vertexIndices.push_back(face.vertexIndices[3]);
				face2.textureIndices.push_back(face.textureIndices[0]);
				face2.textureIndices.push_back(face.textureIndices[2]);
				face2.textureIndices.push_back(face.textureIndices[3]);
				face2.normalIndices.push_back(face.normalIndices[0]);
				face2.normalIndices.push_back(face.normalIndices[2]);
				face2.normalIndices.push_back(face.normalIndices[3]);

				face.vertexIndices.pop_back();
				face.textureIndices.pop_back();
				face.normalIndices.pop_back();

				faces.push_back(face);
				faces.push_back(face2);
			}
			else if (numVertices == 4) // 3 vertices
			{
				std::vector<std::string> chunks = SplitObjLine(line, ' ');
				for (int i = 0; i < 3; i++) // 3 vertices per face
				{
					vertexIndex[i] = 0, uvIndex[i] = 0, normalIndex[i] = 0;
					std::vector <std::string> tokens = SplitObjLine(chunks[i + 1], '/');
					vertexIndex[i] = (tokens[0] == "" ? 0 : std::stoi(tokens[0], nullptr));
					uvIndex[i] = (tokens[1] == "" ? 0 : std::stoi(tokens[1], nullptr));
					normalIndex[i] = (tokens[2] == "" ? 0 : std::stoi(tokens[2], nullptr));
					face.vertexIndices.push_back(vertexIndex[i]);
					face.textureIndices.push_back(uvIndex[i]);
					face.normalIndices.push_back(normalIndex[i]);
				}
				faces.push_back(face);
			}
		}
	}
	file.close();
	return true;
}

void Mesh::CreateMesh()
{
	std::vector<float> interleavedVertices;
	std::vector<unsigned int> indices;

	for (const Face& face : faces)
	{
		for (size_t i = 0; i < face.vertexIndices.size(); i++)
		{
			int vIdx = face.vertexIndices[i] - 1;
			if (vIdx < 0 || vIdx >= vertices.size())
			{
				std::cout << "idx: " << vIdx << " vertices.size(): " << vertices.size() << std::endl; // "Error: Vertex index out of bounds
				std::cout << "Error: Vertex index out of bounds" << std::endl;
				continue;
			}
			interleavedVertices.push_back(vertices[vIdx].x);
			interleavedVertices.push_back(vertices[vIdx].y);
			interleavedVertices.push_back(vertices[vIdx].z);

			if (face.textureIndices.size() > i)
			{
				int uvIdx = face.textureIndices[i] - 1;
				if (uvIdx >= 0 && uvIdx < uvs.size())
				{
					interleavedVertices.push_back(uvs[uvIdx].u);
					interleavedVertices.push_back(uvs[uvIdx].v);
				}
				else
				{
					interleavedVertices.push_back(0.0f);
					interleavedVertices.push_back(0.0f);
				}
			}
			if (face.normalIndices.size() > i)
			{
				int nIdx = face.normalIndices[i] - 1;
				if (nIdx >= 0 && nIdx < normals.size())
				{
					interleavedVertices.push_back(normals[nIdx].nx);
					interleavedVertices.push_back(normals[nIdx].ny);
					interleavedVertices.push_back(normals[nIdx].nz);
				}
				else
				{
					interleavedVertices.push_back(0.0f);
					interleavedVertices.push_back(0.0f);
					interleavedVertices.push_back(0.0f);
				}
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

