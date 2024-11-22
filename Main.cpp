// 3DModelViewer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Window.h"
#include "Time.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "GatsMath.h"
#include "CommonValues.h"

Window mainWindow;
std::vector <Model*> modelList;
std::vector <Shader*> shaderList;

// <This is for custom model: not used>
//unsigned int indices[] = {
//0, 3, 1,
//1, 3, 2,
//2, 3, 0,
//0, 1, 2 };
//
//GLfloat vertices[] = {
//	// x, y, z,				u, v			nx, ny, nz
//	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
//	0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
//	1.0f, -1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
//	0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
//};
//
//Mesh* mesh2 = new Mesh();
//mesh2->CreateCustomModel(vertices, indices, 32, 12);
//meshList.push_back(mesh2);
//
//unsigned int floorIndices[] = {
//0, 2, 1,
//1, 2, 3
//};
//
//GLfloat floorVertices[] = {
//	// x, y, z,				u, v			nx, ny, nz
//	-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
//	10.0f, 0.0f, -10.0f,	10.0f, 0.0f,		0.0f, 1.0f, 0.0f,
//	-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,		0.0f, 1.0f, 0.0f,
//	10.0f, 0.0f, 10.0f,		10.0f, 10.0f,		0.0f, 1.0f, 0.0f
//};
//
//Mesh* mesh3 = new Mesh();
//mesh3->CreateCustomModel(floorVertices, floorIndices, 32, 6);
//meshList.push_back(mesh3);

int main()
{
	// Window
	mainWindow = Window(SCREEN_WIDTH_16_9, SCREEN_HEIGHT_16_9);

	if (mainWindow.Initialize() == false)
	{
		std::cout << "Window initialization failed!" << std::endl;
		return 1;
	}

	// Load Model
	std::vector<std::string> textFilePath = { texture1Path, texture2Path, texture3Path, 
													texture4Path, texture5Path };

	Model* model = new Model(ModelPath, MtlPath, textFilePath);
	if (model->isModelLoaded() == false)
	{
		std::cout << "Model loading failed!" << std::endl;
		return 1;
	}
	modelList.push_back(model);
	modelList[0]->CreateModel();
	
	// Load Shader
	Shader* shader = new Shader();
	shader->CreateFromFiles(VertexShaderPath, FragmentShaderPath);
	shaderList.push_back(shader);

	// Load Camera
	Camera mainCamera = Camera(GatsMath::vec3(0.0f, 0.0f, 2.0f), GatsMath::vec3(0.0f, 1.0f, 0.0f), 
						-90.0f, 0.0f, 1.0f, 0.5f);

	Time::lastTime = glfwGetTime();
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GatsMath::mat4 projection = GatsMath::perspective<float>(GatsMath::ToRadians(45.0f), 
									(GLfloat)mainWindow.GetBufferWidth() / (GLfloat)mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	while (!glfwWindowShouldClose(mainWindow.GetGLFWWindow()))
	{
		Time::UpdateTime();

		glfwPollEvents();

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
		modelList[0]->RenderModel();

		glUseProgram(0);

		glfwSwapBuffers(mainWindow.GetGLFWWindow());
	}

	return 0;
}
