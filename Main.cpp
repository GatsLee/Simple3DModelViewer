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
	mesh2->CreateCustomModel(vertices, indices, 32, 12);
	meshList.push_back(mesh2);

	unsigned int floorIndices[] = {
	0, 2, 1,
	1, 2, 3
	};

	GLfloat floorVertices[] = {
		// x, y, z,				u, v			nx, ny, nz
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,		0.0f, 1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,		0.0f, 1.0f, 0.0f
	};

	Mesh * mesh3 = new Mesh();
	mesh3->CreateCustomModel(floorVertices, floorIndices, 32, 6);
	meshList.push_back(mesh3);

	// Load Texture
	//brickTexture = Texture("Models/LS1.bmp", "bmp");
	//if (brickTexture.LoadTexture() == false)
	//{ 
	//	std::cout << "Failed to load texture!" << std::endl;
	//	return 1;
	//}

	// Load Shader
	Shader* shader = new Shader();
	shader->CreateFromFiles(VertexShaderPath, FragmentShaderPath);
	shaderList.push_back(shader);

	// Load Camera
	Camera mainCamera = Camera(GatsMath::vec3(0.0f, 0.0f, 2.0f), GatsMath::vec3(0.0f, 1.0f, 0.0f), 
						-90.0f, 0.0f, 1.0f, 0.5f);
	Time::lastTime = glfwGetTime();

	// Initiate uniform variables
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GatsMath::mat4 projection = GatsMath::perspective<float>(GatsMath::ToRadians(45.0f), 
									(GLfloat)mainWindow.GetBufferWidth() / (GLfloat)mainWindow.GetBufferHeight(), 0.1f, 100.0f);
	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow.GetGLFWWindow()))
	{
		// Update time
		Time::UpdateTime();

		// Get + Handle user input events
		glfwPollEvents();

		// camera key input
		mainCamera.KeyControl(mainWindow.GetKeys(), Time::GetDeltaTime());
		mainCamera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());
		GatsMath::mat4 viewMatrix = mainCamera.CalculateViewMatrix();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		GLuint uniformModel = shaderList[0]->GetModelLocation();
		GLuint uniformProjection = shaderList[0]->GetProjectionLocation();
		GLuint uniformView = shaderList[0]->GetViewLocation();

		GatsMath::mat4 model(1.0f);
		model = GatsMath::translate<float>(model, GatsMath::vec3(0.0f, 0.0f, -1.0f));
		model = GatsMath::scale<float>(model, GatsMath::vec3(0.3f, 0.3f, 0.3f));
		//model = GatsMath::rotate<float>(model, 0.0f, GatsMath::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, GatsMath::value_ptr<float>(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, GatsMath::value_ptr<float>(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, GatsMath::value_ptr<float>(viewMatrix));
		//brickTexture.UseTexture();
		meshList[1]->RenderMesh();

		model = GatsMath::mat4(1.0f);
		model = GatsMath::translate<float>(model, GatsMath::vec3(0.0f, 0.0f, -2.0f));
		model = GatsMath::scale<float>(model, GatsMath::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, GatsMath::value_ptr<float>(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, GatsMath::value_ptr<float>(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, GatsMath::value_ptr<float>(viewMatrix));
		meshList[2]->RenderMesh();

		glUseProgram(0);

		//std::cout << "View Matrix: " << std::endl;
		//std::cout << viewMatrix << std::endl;

		glfwSwapBuffers(mainWindow.GetGLFWWindow());
	}

	return 0;
}
