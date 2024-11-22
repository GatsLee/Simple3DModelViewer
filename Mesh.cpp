#include "Mesh.h"

Mesh::Mesh()
{
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

bool Mesh::LoadObj(const std::string& fileName)
{
	std::ifstream file(fileName);
	std::ofstream outFile("out.txt");
	if (!file.is_open())
	{
		std::cout << "Error: Could not open file " << fileName << std::endl;
		return false;
	}

	std::string line;
	std::string curActiveMaterial = "";
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string lineType;
		ss >> lineType;
		outFile << line << std::endl;

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
		else if (lineType == "usemtl")
		{
			ss >> curActiveMaterial;
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
					face.activeMaterial = curActiveMaterial;
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
				face2.activeMaterial = curActiveMaterial;

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

//bool Mesh::CreateCustomModel(GLfloat* vertices, unsigned int* indices, 
//								unsigned int numOfVertices, unsigned int numOfIndices)
//{
//	indexCount = numOfIndices;
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &IBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
//	glEnableVertexAttribArray(2);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	return true;
//}

void Mesh::CreateMesh(const std::unordered_map<std::string, Texture*>& textures,
							const std::unordered_map<std::string, struct Material*>& materials)
{
	int vertexIndexCount = 0;
	std::unordered_map<std::string, std::vector<GLfloat>> interleavedVerticesPerMaterial = {};
	std::unordered_map<std::string, std::vector<unsigned int>> indicesPerMaterial = {};

	for (const Face& face : faces)
	{
		std::string activeMaterial = face.activeMaterial;

		for (size_t i = 0; i < face.vertexIndices.size(); i++)
		{
			// Vertices
			int vIdx = face.vertexIndices[i] - 1;
			if (vIdx < 0 || vIdx >= vertices.size())
			{
				continue;
			}
			interleavedVerticesPerMaterial[activeMaterial].push_back(vertices[vIdx].x);
			interleavedVerticesPerMaterial[activeMaterial].push_back(vertices[vIdx].y);
			interleavedVerticesPerMaterial[activeMaterial].push_back(vertices[vIdx].z);

			// Texture
			if (face.textureIndices.size() > i)
			{
				int uvIdx = face.textureIndices[i] - 1;
				if (uvIdx >= 0 && uvIdx < uvs.size())
				{
					interleavedVerticesPerMaterial[activeMaterial].push_back(uvs[uvIdx].u);
					interleavedVerticesPerMaterial[activeMaterial].push_back(uvs[uvIdx].v);
				}
				else
				{
					interleavedVerticesPerMaterial[activeMaterial].push_back(0.0f);
					interleavedVerticesPerMaterial[activeMaterial].push_back(0.0f);
				}
			}
			// Normals
			if (face.normalIndices.size() > i)
			{
				int nIdx = face.normalIndices[i] - 1;
				if (nIdx >= 0 && nIdx < normals.size())
				{
					interleavedVerticesPerMaterial[activeMaterial].push_back(normals[nIdx].nx);
					interleavedVerticesPerMaterial[activeMaterial].push_back(normals[nIdx].ny);
					interleavedVerticesPerMaterial[activeMaterial].push_back(normals[nIdx].nz);
				}
				else
				{
					interleavedVerticesPerMaterial[activeMaterial].push_back(0.0f);
					interleavedVerticesPerMaterial[activeMaterial].push_back(0.0f);
					interleavedVerticesPerMaterial[activeMaterial].push_back(0.0f);
				}
			}
			indicesPerMaterial[activeMaterial].push_back(vertexIndexCount++);
		}
	}

	for (const auto& pair : interleavedVerticesPerMaterial)
	{
		std::string materialName = pair.first;
		std::vector<GLfloat> vertices = pair.second;
		GLuint VAO = 0, VBO = 0, IBO = 0;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesPerMaterial[materialName].size() * sizeof(unsigned int),
			indicesPerMaterial[materialName].data(), GL_STATIC_DRAW);

		// Define vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		// Store VAO and material association
		materialVAOs[materialName] = VAO;
		materialVBOs[materialName] = VBO;
		materialIBOs[materialName] = IBO;
		materialIndexCounts[materialName] = indicesPerMaterial[materialName].size();
	}
}

void Mesh::RenderMesh(const std::unordered_map<std::string, Texture*>& textures,
	const std::unordered_map<std::string, struct Material*>& materials)
{
	for (const auto &pair : materialVAOs)
	{
		std::string materialName = pair.first;
		GLuint VAO = materialVAOs[materialName];
		// Retrieve material and bind its textures
		if (materials.find(materialName) != materials.end())
		{
			Material* material = materials.at(materialName);

			if (textures.find(material->diffuseTexture) != textures.end())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures.at(material->diffuseTexture)->GetTextureID());
			}
		}
		// Bind VAO and render
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, materialIndexCounts[materialName], GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Mesh::ClearMesh()
{
	for (const auto& pair : materialVAOs)
	{
		GLuint VAO = pair.second;
		GLuint VBO = materialVBOs[pair.first];
		GLuint IBO = materialIBOs[pair.first];

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &IBO);
	}
	vertices.clear();
	uvs.clear();
	normals.clear();
	faces.clear();

	materialVAOs.clear();
	materialVBOs.clear();
	materialIBOs.clear();
	materialIndexCounts.clear();
}

void Mesh::CalculateAverageNormals(unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount, unsigned int vLength, unsigned int uvLength, unsigned int normalLength)
{
}

