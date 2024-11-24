#include "Texture.h"

Texture::Texture()
{
	fileLocation = "";
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
}

Texture::Texture(std::string fileLocation, std::string fileType)
{
	this->fileLocation = fileLocation;
	this->fileName = fileLocation.substr(fileLocation.find_last_of("/\\") + 1);
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
	ClearTexture();
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

	if (textureData == nullptr)
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

bool Texture::LoadTextureA()
{
	return false;
}

void Texture::UseTexture(GLuint textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	delete[] textureData;
	textureData = nullptr;
	fileLocation = "";
}

unsigned char* Texture::ProcessBitMap()
{
	std::ifstream file(fileLocation, std::ios::binary);
	if (!file)
	{
		std::cerr << "Error: Could not open BMP file at " << fileLocation << std::endl;
		return nullptr;
	}

	unsigned char fileHeader[14];
	file.read(reinterpret_cast<char*>(fileHeader), 14);
	if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
	{
		std::cerr << "Error: Not a valid BMP file" << std::endl;
		return nullptr;
	}

	int dataOffset = *reinterpret_cast<int*>(&fileHeader[10]);

	unsigned char infoHeader[40];
	file.read(reinterpret_cast<char*>(infoHeader), 40);

	width = *reinterpret_cast<int*>(&infoHeader[4]);
	height = *reinterpret_cast<int*>(&infoHeader[8]);
	bitDepth = *reinterpret_cast<short*>(&infoHeader[14]);

	if (bitDepth != 24)
	{
		std::cerr << "Error: Only 24-bit BMP files are supported" << std::endl;
		return nullptr;
	}

	int row_padded = (width * 3 + 3) & (~3);
	textureData = new unsigned char[row_padded * height];

	file.seekg(dataOffset, std::ios::beg);

	unsigned char* rgbData = new unsigned char[width * height * 3];

	for (int y = 0; y < height; y++)
	{
		int rowIndex = (height - 1 - y) * width * 3;
		file.read(reinterpret_cast<char*>(textureData), row_padded);
		for (int x = 0; x < width; x++)
		{
			int bmpIndex = x * 3;
			rgbData[rowIndex + bmpIndex] = textureData[bmpIndex + 2];   // R
			rgbData[rowIndex + bmpIndex + 1] = textureData[bmpIndex + 1]; // G
			rgbData[rowIndex + bmpIndex + 2] = textureData[bmpIndex];   // B
		}
	}

	file.close();
	return rgbData;
}
