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
#include "CommonValues.h"

Window mainWindow;
Camera mainCamera;
std::vector <Mesh*> meshList;
std::vector <Shader*> shaderList;
//Camera mainCamera;

Texture skullTexture;

int main()
{
	// Initialize Window
	mainWindow = Window(SCREEN_WIDTH_16_9, SCREEN_HEIGHT_16_9);

	if (mainWindow.Initialize() == false)
	{
		std::cout << "Window initialization failed!" << std::endl;
		return 1;
	}

	// Load Model
	Mesh * mesh = new Mesh();
	meshList.push_back(mesh);
	meshList[0]->LoadModel("Models/LibertStatue.obj");
	meshList[0]->CreateMesh();

	// Load Shader
	Shader* shader = new Shader();
	shaderList.push_back(shader);
	shaderList[0]->CreateFromFiles(VertexShaderPath, FragmentShaderPath);

	// Load Camera
	mainCamera = Camera(GatsMath::vec3(0.0f, 0.0f, 0.0f), GatsMath::vec3(0.0f, 1.0f, 0.0f), 
						-90.0f, 0.0f, 5.0f, 0.1f);

	// Initiate uniform variables

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow.GetGLFWWindow()))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// camera key input
		//mainCamera.KeyControl(mainWindow.GetKeys(), Time::GetDeltaTime());
		//mainCamera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//shaderList[0]->UseShader();

		//GatsMath::mat4 model(1.0f);

		//model = GatsMath::translate<float>(model, GatsMath::vec3(0.0f, 0.0f, -2.5f));
		//model = GatsMath::scale<float>(model, GatsMath::vec3(0.4f, 0.4f, 0.4f));
		//model = GatsMath::rotate<float>(model, 0.0f, GatsMath::vec3(0.0f, 1.0f, 0.0f));



		//meshList[0]->RenderMesh();


		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow.GetGLFWWindow());

		// Update time
		Time::UpdateTime();
	}

	return 0;
}
