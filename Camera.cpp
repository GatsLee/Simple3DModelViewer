#include "Camera.h"

Camera::Camera()
{
	position = GatsMath::vec3(0.0f, 0.0f, 0.0f);
	up = GatsMath::vec3(0.0f, 1.0f, 0.0f);
	forward = GatsMath::vec3(0.0f, 0.0f, -1.0f);
	worldUp = up;
	yaw = -90.0f;
	pitch = 0.0f;
	moveSpeed = 1.0f;
	turnSpeed = 0.1f;

	//Update();
}

Camera::Camera(GatsMath::vec3 position, GatsMath::vec3 startUp, float startYaw, float startPitch, float MoveSpeed, float startTurnSpeed)
{
	this->position = position;
	this->up = startUp;
	this->worldUp = startUp;
	this->yaw = startYaw;
	this->pitch = startPitch;
	this->forward = GatsMath::vec3(0.0f, 0.0f, -1.0f);
	this->moveSpeed = MoveSpeed;
	this->turnSpeed = startTurnSpeed;

	//Update();
}

Camera::~Camera()
{
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	float velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += forward * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= forward * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_Q])
	{
		position += up * velocity;
	}

	if (keys[GLFW_KEY_E])
	{
		position -= up * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	//Update();
}
