#include "Shader.h"

Shader::Shader()
{
	pointLightCount = 0;
	spotLightCount = 0;
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
}

Shader::~Shader()
{
}

bool Shader::CreateFromFiles(std::string vertexLocation, std::string fragmentLocation)
{
	vertexShader = ReadFile(vertexLocation);
	fragmentShader = ReadFile(fragmentLocation);

	if (vertexShader == "" || fragmentShader == "")
	{
		return false;
	}
	
	CompileShader();

	return true;
}

GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::GetViewLocation()
{
	return uniformView;
}

GLuint Shader::GetDiffuseTextureSamplerLocation()
{
	return uniformDiffuseTextureSampler;
}

GLuint Shader::GetUseDefaultColorLocation()
{
	return uniformUseDefaultColor;
}

GLuint Shader::GetActiveTextureIndexLocation()
{
	return uniformActiveTextureIndex;
}

void Shader::SetUseDefaultColour(bool useDefaultColour)
{
	glUniform1i(uniformUseDefaultColor, useDefaultColour);
}

void Shader::SetTexture(GLuint textureUnit)
{
	glUniform1i(uniformDiffuseTextureSampler, textureUnit);
}

void Shader::SetTextureIndex(int index)
{
	glUniform1i(uniformActiveTextureIndex, index);
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

std::string Shader::ReadFile(std::string fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cout << "Failed to read " << fileLocation << "! File does not exist." << std::endl;
		return nullptr;
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();

	return content;
}

bool Shader::CompileShader()
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		std::cout << "Error creating shader program!" << std::endl;
		return false;
	}

	AddShader(shaderID, vertexShader.c_str(), GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentShader.c_str(), GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: " << eLog << std::endl;
		return false;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: " << eLog << std::endl;
		return false;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformDiffuseTextureSampler = glGetUniformLocation(shaderID, "diffuseTexture");
	uniformUseDefaultColor = glGetUniformLocation(shaderID, "useDefaultColour");
	uniformActiveTextureIndex = glGetUniformLocation(shaderID, "activeTextureIndex");

	return true;
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << " shader: " << eLog << std::endl;
		return;
	}

	glAttachShader(theProgram, theShader);
}
