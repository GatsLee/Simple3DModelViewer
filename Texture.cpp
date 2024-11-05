#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(std::string fileLocation, std::string fileType)
{
	this->fileLocation = fileLocation;
	if (fileType == "bmp")
	{
		this->fileType = BMP;
	}
	else if (fileType == "jpg")
	{
		this->fileType = JPG;
	}
	else if (fileType == "png")
	{
		this->fileType = PNG;
	}
	else
	{
		this->fileType = UNKNOWN;
	}

	textureData = nullptr;

	width = 0;
	height = 0;
	bitDepth = 0;
}

Texture::~Texture()
{
}

bool Texture::LoadTexture()
{
	if (fileType == BMP)
	{
		textureData = ProcessBitMap();
	}
	else if (fileType == JPG)
	{
		//textureData = ProcessJPG();
	}
	else if (fileType == PNG)
	{
		//textureData = ProcessPNG();
	}
	else
	{
		std::cout << "Error: File type not supported" << std::endl;
		return false;
	}

	if (!textureData)
	{
		std::cout << "Error: Failed to load texture" << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

unsigned char* Texture::ProcessBitMap()
{
	return nullptr;
}
