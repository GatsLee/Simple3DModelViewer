#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>

class Window
{
public:
	Window(GLint windowWidth = 800, GLint windowHeight = 600);
	~Window();

	GLFWwindow* GetGLFWWindow() { return mainWindow; }

	bool Initialize();

	GLfloat getBufferWidth() const{ return bufferWidth; }
	GLfloat getBufferHeight() const { return bufferHeight; }

	//bool LoadIconBMP(const char* filename, int& width, int& height, std::vector<unsigned char>& pixelData);

private:
	GLFWwindow* mainWindow;
	GLint windowWidth, windowHeight;
	bool keys[1024];

	GLint bufferWidth, bufferHeight;

	int iconWidth, iconHeight;

	//void createCallbacks();
	//static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	//void createKeyCallbacks();

	//bool LoadIconBMP(const char* filename, std::vector<unsigned char>& pixelData);

};

