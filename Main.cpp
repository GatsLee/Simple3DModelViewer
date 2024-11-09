// 3DModelViewer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Window.h"
#include "Time.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "GatsMath.h"

Window mainWindow;
//std::vector <Mesh*> meshList;
//std::vector <Shader*> shaderList;
//Camera mainCamera;

Texture skullTexture;

static const char* vertexShaderPath = "shaders/shader.vert";
static const char* fragmentShaderPath = "shaders/shader.frag";

int main()
{
	// Initialize Window
	mainWindow = Window(800, 600);

	if (mainWindow.Initialize() == false)
	{
		std::cout << "Window initialization failed!" << std::endl;
		return 1;
	}

	// Load Model
	//Mesh mesh;
	//mesh.LoadModel("models/skull.obj");

	// Load Shader
	//Shader shader;
	//shader.LoadShader(vertexShaderPath, fragmentShaderPath);

	GatsMath::vec2 vec(1, 2);

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow.GetGLFWWindow()))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow.GetGLFWWindow());

		// Update time
		Time::UpdateTime();
	}

	return 0;
}
