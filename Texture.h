#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

class Texture
{
public:
	typedef enum fileType {
		BMP,
		JPG,
		PNG,
		UNKNOWN
	} e_fileType;


	Texture();
	Texture(std::string fileLocation, std::string fileType);
	~Texture();

	bool LoadTexture();
	bool LoadTextureA();
	void UseTexture(GLuint textureUnit);
	void ClearTexture();

	std::string GetFileLocation() const { return fileLocation; }
	std::string GetFileName() const { return fileName; }
	GLuint GetTextureID() const { return textureID; }

private:
	e_fileType fileType;
	GLuint textureID;
	int width, height, bitDepth;

	unsigned char* textureData;

	std::string fileLocation;
	std::string fileName;

	unsigned char* ProcessBitMap();
};

