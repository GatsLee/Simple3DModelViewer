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

	Update();
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

	Update();
}

Camera::~Camera()
{
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	float velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position =  position + forward * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position = position - forward * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position  = position - right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position = position + right * velocity;
	}

	if (keys[GLFW_KEY_Q])
	{
		position = position + up * velocity;
	}

	if (keys[GLFW_KEY_E])
	{
		position = position - up * velocity;
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

	Update();
}

GatsMath::mat4 Camera::CalculateViewMatrix() const
{
	return GatsMath::lookAt<float>(position, position + forward, up);
}

void Camera::Update()
{
	forward.x = cos(GatsMath::ToRadians(yaw)) * cos(GatsMath::ToRadians(pitch));
	forward.y = sin(GatsMath::ToRadians(pitch));
	forward.z = sin(GatsMath::ToRadians(yaw)) * cos(GatsMath::ToRadians(pitch));
	forward = forward.normalize();

	right = GatsMath::cross(forward, worldUp).normalize();
	up = GatsMath::cross(right, forward).normalize();
}
