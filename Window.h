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

	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }

	float GetBufferWidth() const{ return static_cast<GLfloat>(bufferWidth); }
	float GetBufferHeight() const { return static_cast<GLfloat>(bufferHeight); }

	void SwapBuffers() { glfwSwapBuffers(mainWindow); }

	bool* GetKeys() { return keys; }
	GLfloat GetXChange();
	GLfloat GetYChange();

	//bool LoadIconBMP(const char* filename, int& width, int& height, std::vector<unsigned char>& pixelData);

private:
	GLFWwindow* mainWindow;
	GLuint windowWidth, windowHeight;
	GLuint bufferWidth, bufferHeight;
	
	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	int iconWidth, iconHeight;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);

	//bool LoadIconBMP(const char* filename, std::vector<unsigned char>& pixelData);

};

