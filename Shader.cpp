#include "Shader.h"

Shader::Shader()
{
	pointLightCount = 0;
	spotLightCount = 0;
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
	uniformEyePosition = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;
}

Shader::~Shader()
{
}

bool Shader::CreateFromFiles(std::string vertexLocation, std::string fragmentLocation)
{
	return true;
}

GLuint Shader::GetModelLocation()
{
	return GLuint();
}

GLuint Shader::GetProjectionLocation()
{
	return GLuint();
}

GLuint Shader::GetViewLocation()
{
	return GLuint();
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return GLuint();
}

GLuint Shader::GetAmbientColourLocation()
{
	return GLuint();
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return GLuint();
}

GLuint Shader::GetDirectionLocation()
{
	return GLuint();
}

GLuint Shader::GetEyePositionLocation()
{
	return GLuint();
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return GLuint();
}

GLuint Shader::GetShininessLocation()
{
	return GLuint();
}

void Shader::UseShader()
{
}

void Shader::ClearShader()
{
}
