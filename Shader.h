#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CommonValues.h"

class Shader
{
public:
	Shader();
	~Shader();

	bool CreateFromFiles(std::string vertexLocation, std::string fragmentLocation);

	GLuint GetShaderID() const { return shaderID; }

	GLuint GetModelLocation();
	GLuint GetProjectionLocation();
	GLuint GetViewLocation();
	GLuint GetDiffuseTextureSamplerLocation();
	GLuint GetUseDefaultColorLocation();
	GLuint GetActiveTextureIndexLocation();

	void SetUseDefaultColour(bool useDefaultColour);
	void SetTexture(GLuint textureUnit);

	void UseShader();
	void ClearShader();

private:
	std::string vertexShader;
	std::string fragmentShader;

	int pointLightCount;
	int spotLightCount;

	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	GLuint uniformDiffuseTextureSampler;
	//GLuint uniformActiveTextureIndex;

	GLuint uniformUseDefaultColor;

	std::string ReadFile(std::string fileLocation);
	bool CompileShader();
	void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
};
