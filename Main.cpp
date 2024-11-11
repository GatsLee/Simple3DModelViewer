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
Texture brickTexture;


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
	
	unsigned int indices[] = {
	0, 3, 1,
	1, 3, 2,
	2, 3, 0,
	0, 1, 2 };

	GLfloat vertices[] = {
		// x, y, z,				u, v			nx, ny, nz
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	Mesh * mesh2 = new Mesh();
	meshList.push_back(mesh2);
	meshList[1]->CreateCustomModel(vertices, indices, 32, 12);

	// Load Texture
	brickTexture = Texture("Models/LS1.bmp", "bmp");
	if (brickTexture.LoadTexture() == false)
	{
		std::cout << "Failed to load texture!" << std::endl;
		return 1;
	}

	// Load Shader
	Shader* shader = new Shader();
	shaderList.push_back(shader);
	shaderList[0]->CreateFromFiles(VertexShaderPath, FragmentShaderPath);

	// Load Camera
	mainCamera = Camera(GatsMath::vec3(0.0f, 0.0f, 0.0f), GatsMath::vec3(0.0f, 1.0f, 0.0f), 
						-90.0f, 0.0f, 5.0f, 0.5f);


	// Initiate uniform variables
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GatsMath::mat4 projection = GatsMath::perspective<float>(GatsMath::ToRadians(45.0f), 
									mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	std::cout << projection << std::endl;

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow.GetGLFWWindow()))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// camera key input
		mainCamera.KeyControl(mainWindow.GetKeys(), Time::GetDeltaTime());
		mainCamera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		GLuint uniformModel = shaderList[0]->GetModelLocation();
		GLuint uniformProjection = shaderList[0]->GetProjectionLocation();
		GLuint uniformView = shaderList[0]->GetViewLocation();

		GatsMath::mat4 model(1.0f);
		model = GatsMath::translate<float>(model, GatsMath::vec3(0.0f, 0.0f, -2.5f));
		model = GatsMath::scale<float>(model, GatsMath::vec3(0.4f, 0.4f, 0.4f));
		//model = GatsMath::rotate<float>(model, 0.0f, GatsMath::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, GatsMath::value_ptr<float>(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, GatsMath::value_ptr<float>(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, GatsMath::value_ptr<float>(mainCamera.CalculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		glfwSwapBuffers(mainWindow.GetGLFWWindow());

		// Update time
		Time::UpdateTime();
	}

	return 0;
}
